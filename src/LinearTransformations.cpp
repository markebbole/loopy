#include "LinearTransformations.h"

cv::Mat Make3x3Matrix(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    float data[9] = {a, b, c,
                     d, e, f,
                     g, h, i};

    return cv::Mat(3, 3, CV_32F, data).clone();
}

cv::Mat Make3x3TranslationMatrix(float x, float y)
{
    return Make3x3Matrix(1, 0, x, 0, 1, y, 0, 0, 1);
}

cv::Mat Make3x3ScalingMatrix(float x, float y)
{
    return Make3x3Matrix(x, 0, 0, 0, y, 0, 0, 0, 1);
}

cv::Mat Make3x3RotationMatrix(float theta)
{
    return Make3x3Matrix(cos(theta), -sin(theta), 0, sin(theta), cos(theta), 0, 0, 0, 1);
}

cv::Mat LinearTransformationNode::process(LoopyFunctionInput inputs)
{
    const cv::Mat& input = inputs[imageInput]->getOutput();

    cv::Mat output;
    cv::warpPerspective(input, output, transform_3x3, cv::Size(input.cols, input.rows), cv::INTER_LINEAR);
    return output;
}

cv::Mat TranslateNode::process(LoopyFunctionInput inputs)
{
    float x = getFloatParam("x");
    float y = getFloatParam("y");
    transform_3x3 = Make3x3TranslationMatrix(x, y);
    LinearTransformationNode::process(inputs);
}

cv::Mat ScaleNode::process(LoopyFunctionInput inputs)
{
    float x = getFloatParam("x");
    float y = getFloatParam("y");
    float centerX = getFloatParam("centerX");
    float centerY = getFloatParam("centerY");
    cv::Mat t1 = Make3x3TranslationMatrix(-centerX, -centerY);
    cv::Mat scaleMatrix = t1.inv() * Make3x3ScalingMatrix(x, y) * t1;
    transform_3x3 = scaleMatrix;
    LinearTransformationNode::process(inputs);
}

cv::Mat RotateNode::process(LoopyFunctionInput inputs)
{
    float rotationDegrees = getFloatParam("degrees");
    float centerX = getFloatParam("centerX");
    float centerY = getFloatParam("centerY");
    float theta = rotationDegrees * (CV_PI / 180);
    cv::Mat t1 = Make3x3TranslationMatrix(-centerX, -centerY);
    cv::Mat mult = t1.inv() * Make3x3RotationMatrix(theta) * t1;
    transform_3x3 = mult;
    LinearTransformationNode::process(inputs);
}