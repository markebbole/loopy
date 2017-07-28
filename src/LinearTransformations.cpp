#include "LinearTransformations.h"

LinearTransformationFunction LinearTransformationFunction::Translate(float x, float y)
{
    LinearTransformationFunction translateFunction(1, 0, x,
                                                   0, 1, y,
                                                   0, 0, 1);
    return translateFunction;
}

LinearTransformationFunction LinearTransformationFunction::Scale(float x, float y, float centerX, float centerY)
{
    LinearTransformationFunction t1 = Translate(-centerX, -centerY);
    LinearTransformationFunction scaleFunction(x, 0, 0,
                                               0, y, 0,
                                               0, 0, 1);
    return t1.inverse() * scaleFunction * t1;
}

LinearTransformationFunction LinearTransformationFunction::Rotate(float rotationDegrees, float centerX, float centerY)
{
    float theta = rotationDegrees * (CV_PI / 180);

    LinearTransformationFunction t1 = Translate(-centerX, -centerY);
    LinearTransformationFunction rotationFunction(cos(theta), -sin(theta), 0,
                                                   sin(theta),  cos(theta), 0,
                                                           0,           0, 1);
    return t1.inverse() * rotationFunction * t1;
}

cv::Mat LinearTransformationFunction::operator()(LoopyFunctionInput inputs)
{
  const cv::Mat& input = inputs[imageInput]->getOutput();

  cv::Mat output;
    cv::warpPerspective(input, output, transform_3x3, cv::Size(input.cols, input.rows));
    return output;
}

LinearTransformationFunction::LinearTransformationFunction(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
  float data[9] = {a, b, c,
                 d, e, f,
                 g, h, i};

  transform_3x3 = cv::Mat(3, 3, CV_32F, data).clone();
}

LinearTransformationFunction LinearTransformationFunction::inverse()
{
  LinearTransformationFunction t;
  t.transform_3x3 = this->transform_3x3.inv();
  return t;
}

LinearTransformationFunction LinearTransformationFunction::operator*(const LinearTransformationFunction &a)
{
  LinearTransformationFunction t;
  t.transform_3x3 = transform_3x3 * a.transform_3x3;
  return t;
}