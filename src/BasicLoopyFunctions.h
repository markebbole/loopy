#ifndef BASIC_LOOPY_FUNCTIONS
#define BASIC_LOOPY_FUNCTIONS

#include "LoopyNode.h"
#include "LinearTransformations.h"
#include "BinaryPixelOperators.h"
#import <opencv2/opencv.hpp>
#import <functional>
#include <vector>
#include <string>
#include <map>

/**
 * This file contains some basic LoopyFunctions that I feel will be useful for lots of situations.
 */

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

// might be better to just make these static functions that construct a binaryfunction with the right operator?
struct AdditionFunction : public BinaryFunction
{
    std::string foregroundKey;
    std::string backgroundKey;
	AdditionFunction(float foregroundMultiplier) : BinaryFunction(new AddPixelOperator(foregroundMultiplier), "F", "B") 
	{
        foregroundKey = "F";
        backgroundKey = "B";
	}
};

struct MultiplyFunction : public BinaryFunction
{
    std::string foregroundKey;
    std::string backgroundKey;
    MultiplyFunction() : BinaryFunction(new MultiplyPixelOperator(), "F", "B")
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