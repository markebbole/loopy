#ifndef BASIC_LOOPY_FUNCTIONS
#define BASIC_LOOPY_FUNCTIONS

#include "LoopyNode.h"
#import <opencv2/opencv.hpp>
#import <functional>
#include <vector>
#include <string>
#include <map>

/**
 * This file contains some basic LoopyFunctions that I feel will be useful for lots of situations.
 */

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

};

static LinearTransformationFunction Translate(float x, float y)
{
	LinearTransformationFunction translateFunction(1, 0, x,
											       0, 1, y,
											       0, 0, 1);
	return translateFunction;
}

static LinearTransformationFunction Scale(float x, float y, float centerX, float centerY)
{
	LinearTransformationFunction t1 = Translate(-centerX, -centerY);
	LinearTransformationFunction scaleFunction(x, 0, 0,
											   0, y, 0,
											   0, 0, 1);
	return t1.inverse() * scaleFunction * t1;
}

static LinearTransformationFunction Rotate(float rotationDegrees, float centerX, float centerY)
{
	float theta = rotationDegrees * (CV_PI / 180);

	LinearTransformationFunction t1 = Translate(-centerX, -centerY);
	LinearTransformationFunction rotationFunction(cos(theta), -sin(theta), 0,
		                                          sin(theta),  cos(theta), 0,
		                                                   0,           0, 1);
	return t1.inverse() * rotationFunction * t1;
}

struct AdditionFunction
{
	std::string backgroundKey = "Background";
	std::string foregroundKey = "Foreground";

	float foregroundMultiplier;

	AdditionFunction(float foregroundMultiplier) : foregroundMultiplier(foregroundMultiplier) 
	{
	}

	cv::Mat operator()(LoopyFunctionInput inputs);
};
 
#endif