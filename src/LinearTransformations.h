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
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

struct ScaleNode : public LinearTransformationNode
{
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

struct RotateNode : public LinearTransformationNode
{
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

#endif