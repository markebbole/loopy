#ifndef LINEAR_TRANSFORMATIONS
#define LINEAR_TRANSFORMATIONS

#include "BasicLoopyFunctions.h"
/**
 * Perform a linear transformation on an input with key ImageInput
 */

struct LinearTransformationFunction
{
    cv::Mat transform_3x3;

    std::string imageInput = "ImageInput";

    LinearTransformationFunction(float a, float b, float c, float d, float e, float f, float g, float h, float i);

    LinearTransformationFunction() : LinearTransformationFunction(0,0,0,0,0,0,0,0,0)
    {
    }

    LinearTransformationFunction inverse();

    LinearTransformationFunction operator*(const LinearTransformationFunction &a);

    cv::Mat operator()(LoopyFunctionInput inputs);

    static LinearTransformationFunction Translate(float x, float y);

    static LinearTransformationFunction Scale(float x, float y, float centerX, float centerY);

    static LinearTransformationFunction Rotate(float rotationDegrees, float centerX, float centerY);

};

#endif