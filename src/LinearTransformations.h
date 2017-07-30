#ifndef LINEAR_TRANSFORMATIONS
#define LINEAR_TRANSFORMATIONS

#include "BasicLoopyFunctions.h"
/**
 * Perform a linear transformation on an input with key ImageInput
 */

struct LinearTransformationNode : public LoopyNode
{
    cv::Mat transform_3x3;

    std::string imageInput = "ImageInput";

    LinearTransformationNode(float a, float b, float c, float d, float e, float f, float g, float h, float i);

    LinearTransformationNode() : LinearTransformationNode(0,0,0,0,0,0,0,0,0)
    {
    }

    LinearTransformationNode inverse();

    LinearTransformationNode operator*(const LinearTransformationNode &a);

    virtual cv::Mat process(LoopyFunctionInput inputs);

    static LinearTransformationNode Translate(float x, float y);

    static LinearTransformationNode Scale(float x, float y, float centerX, float centerY);

    static LinearTransformationNode Rotate(float rotationDegrees, float centerX, float centerY);

};

#endif