#include "LinearTransformations.h"

LinearTransformationNode LinearTransformationNode::Translate(float x, float y)
{
    LinearTransformationNode translateFunction(1, 0, x,
                                                   0, 1, y,
                                                   0, 0, 1);
    return translateFunction;
}

LinearTransformationNode LinearTransformationNode::Scale(float x, float y, float centerX, float centerY)
{
    LinearTransformationNode t1 = Translate(-centerX, -centerY);
    LinearTransformationNode scaleFunction(x, 0, 0,
                                               0, y, 0,
                                               0, 0, 1);
    return t1.inverse() * scaleFunction * t1;
}

LinearTransformationNode LinearTransformationNode::Rotate(float rotationDegrees, float centerX, float centerY)
{
    float theta = rotationDegrees * (CV_PI / 180);

    LinearTransformationNode t1 = Translate(-centerX, -centerY);
    LinearTransformationNode rotationFunction(cos(theta), -sin(theta), 0,
                                                   sin(theta),  cos(theta), 0,
                                                           0,           0, 1);
    return t1.inverse() * rotationFunction * t1;
}

cv::Mat LinearTransformationNode::process(LoopyFunctionInput inputs)
{
  const cv::Mat& input = inputs[imageInput]->getOutput();

  cv::Mat output;
    cv::warpPerspective(input, output, transform_3x3, cv::Size(input.cols, input.rows));
    return output;
}

LinearTransformationNode::LinearTransformationNode(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
  float data[9] = {a, b, c,
                 d, e, f,
                 g, h, i};

  transform_3x3 = cv::Mat(3, 3, CV_32F, data).clone();
}

LinearTransformationNode LinearTransformationNode::inverse()
{
  LinearTransformationNode t;
  t.transform_3x3 = this->transform_3x3.inv();
  return t;
}

LinearTransformationNode LinearTransformationNode::operator*(const LinearTransformationNode &a)
{
  LinearTransformationNode t;
  t.transform_3x3 = transform_3x3 * a.transform_3x3;
  return t;
}