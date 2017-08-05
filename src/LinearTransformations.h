#ifndef LINEAR_TRANSFORMATIONS
#define LINEAR_TRANSFORMATIONS

#include "BasicLoopyNodes.h"

extern cv::Mat Make3x3TranslationMatrix(float x, float y);

extern cv::Mat Make3x3ScalingMatrix(float x, float y);

extern cv::Mat Make3x3RotationMatrix(float theta);
/**
 * Perform a linear transformation on an input with key ImageInput
 */

struct LinearTransformationNode : public LoopyNode
{
    cv::Mat transform_3x3;

    std::string imageInput = "imageInput";

    LinearTransformationNode() : LoopyNode() {}

    virtual cv::Mat process(LoopyFunctionInput inputs);
};

struct TranslateNode : public LinearTransformationNode
{
    virtual void setFunctionInputs(json inputs) {
        LinearTransformationNode::setFunctionInputs(inputs);
        float x = inputs["x"];
        float y = inputs["y"];
        transform_3x3 = Make3x3TranslationMatrix(x, y);
    }
};

struct ScaleNode : public LinearTransformationNode
{
    virtual void setFunctionInputs(json inputs) {
        LinearTransformationNode::setFunctionInputs(inputs);
        float x = inputs["x"];
        float y = inputs["y"];
        float centerX = inputs["centerX"];
        float centerY = inputs["centerY"];
        cv::Mat t1 = Make3x3TranslationMatrix(-centerX, -centerY);
        cv::Mat scaleMatrix = t1.inv() * Make3x3ScalingMatrix(x, y) * t1;
        transform_3x3 = scaleMatrix;
    }
};

struct RotateNode : public LinearTransformationNode
{
    virtual void setFunctionInputs(json inputs) {
        LinearTransformationNode::setFunctionInputs(inputs);
        float rotationDegrees = inputs["degrees"];
        float centerX = inputs["centerX"];
        float centerY = inputs["centerY"];
        float theta = rotationDegrees * (CV_PI / 180);
        cv::Mat t1 = Make3x3TranslationMatrix(-centerX, -centerY);
        cv::Mat mult = t1.inv() * Make3x3RotationMatrix(theta) * t1;
        transform_3x3 = mult;
    }
};
#endif