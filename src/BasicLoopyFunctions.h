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

struct BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second)
    {
        return cv::Vec4b();
    }
};

struct AddPixelOperator : public BinaryPixelOperator
{
    float foregroundMultiplier;
    AddPixelOperator(float foregroundMultiplier) : BinaryPixelOperator() {
        this->foregroundMultiplier = foregroundMultiplier;
    }
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second)
    {
        if (first[3] == 0) {
            return second;
        } else {
            return foregroundMultiplier * first + (1-foregroundMultiplier) * second;
        }
    }
};

struct AddPixelModOperator : public BinaryPixelOperator
{
    float foregroundMultiplier;
    AddPixelModOperator(float foregroundMultiplier) : BinaryPixelOperator() {
        this->foregroundMultiplier = foregroundMultiplier;
    }
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second)
    {
        if (first[3] == 0) {
            return second;
        } else {
            return cv::Vec4b((first[0]+second[0])%256, (first[1]+second[1])%256, (first[2]+second[2])%256, 1);
        }
    }
};



struct BinaryFunction
{
private:
    std::string firstKey;
    std::string secondKey;
public:
    BinaryPixelOperator* op;

    BinaryFunction(BinaryPixelOperator* op, std::string f, std::string s) : op(op), firstKey(f), secondKey(s)
    {
    }

    cv::Mat operator()(LoopyFunctionInput inputs);
};


struct AdditionFunction : public BinaryFunction
{
    std::string foregroundKey;
    std::string backgroundKey;
	AdditionFunction(float foregroundMultiplier) : BinaryFunction(new AddPixelModOperator(foregroundMultiplier), "F", "B") 
	{
        foregroundKey = "F";
        backgroundKey = "B";
	}
};

struct SpeckledNoise
{
    std::string imageKey = "Image";
    float speckleFrequency;
    bool colored;

    SpeckledNoise(float speckleFrequency, bool colored) : speckleFrequency(speckleFrequency), colored(colored) {}
    cv::Mat operator()(LoopyFunctionInput inputs);
};
 
#endif