#include "LinearTransformations.h"

static cv::Mat Make3x3Matrix(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
  float data[9] = {a, b, c,
   d, e, f,
   g, h, i};

   return cv::Mat(3, 3, CV_32F, data).clone();
 }

 static cv::Mat Make3x3TranslationMatrix(float x, float y)
 {
  return Make3x3Matrix(1, 0, x, 0, 1, y, 0, 0, 1);
}

static cv::Mat Make3x3ScalingMatrix(float x, float y)
{
  return Make3x3Matrix(x, 0, 0, 0, y, 0, 0, 0, 1);
}

static cv::Mat Make3x3RotationMatrix(float theta)
{
  return Make3x3Matrix(cos(theta), -sin(theta), 0, sin(theta), cos(theta), 0, 0, 0, 1);
}

LinearTransformationNode* LinearTransformationNode::Translate(float x, float y)
{
  LinearTransformationNode* translateFunction = new LinearTransformationNode(Make3x3TranslationMatrix(x, y));
  return translateFunction;
}

LinearTransformationNode* LinearTransformationNode::Scale(float x, float y, float centerX, float centerY)
{
  cv::Mat t1 = Make3x3TranslationMatrix(-centerX, -centerY);
  cv::Mat scaleMatrix = t1.inv() * Make3x3ScalingMatrix(x, y) * t1;
  LinearTransformationNode *scale = new LinearTransformationNode(scaleMatrix);
  return scale;
}

LinearTransformationNode* LinearTransformationNode::Rotate(float rotationDegrees, float centerX, float centerY)
{
  float theta = rotationDegrees * (CV_PI / 180);

  cv::Mat t1 = Make3x3TranslationMatrix(-centerX, -centerY);
  cv::Mat mult = t1.inv() * Make3x3RotationMatrix(theta) * t1;

  LinearTransformationNode *rotation = new LinearTransformationNode(mult);
  return rotation;
}

cv::Mat LinearTransformationNode::process(LoopyFunctionInput inputs)
{
  const cv::Mat& input = inputs[imageInput]->getOutput();

  cv::Mat output;
  cv::warpPerspective(input, output, transform_3x3, cv::Size(input.cols, input.rows));
  return output;
}

LinearTransformationNode::LinearTransformationNode(cv::Mat transformationMatrix)
{
  transform_3x3 = transformationMatrix;
}