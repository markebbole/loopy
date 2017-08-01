#ifndef LINEAR_TRANSFORMATIONS
#define LINEAR_TRANSFORMATIONS

#include "BasicLoopyNodes.h"

/**
 * Perform a linear transformation on an input with key ImageInput
 */

struct LinearTransformationNode : public LoopyNode
{
    cv::Mat transform_3x3;

    std::string imageInput = "ImageInput";

    LinearTransformationNode(cv::Mat transformationMatrix);

    LinearTransformationNode inverse();

    LinearTransformationNode operator*(const LinearTransformationNode &a);

    virtual cv::Mat process(LoopyFunctionInput inputs);

    static LinearTransformationNode* Translate(float x, float y);

    static LinearTransformationNode* Scale(float x, float y, float centerX, float centerY);

    static LinearTransformationNode* Rotate(float rotationDegrees, float centerX, float centerY);

};

#endif