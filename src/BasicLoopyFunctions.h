#ifndef BASIC_LOOPY_FUNCTIONS
#define BASIC_LOOPY_FUNCTIONS

#include "LoopyNode.h"

#include <stdlib.h>
#include "LinearTransformations.h"
#include "BinaryPixelOperators.h"

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
        backgroundKey = "B"; //ugh
	}
};

struct MultiplyFunction : public BinaryFunction
{
    std::string foregroundKey;
    std::string backgroundKey;
    MultiplyFunction() : BinaryFunction(new MultiplyPixelOperator(), "F", "B")
    {
        foregroundKey = "F";
        backgroundKey = "B"; //ugh
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

struct RandomWalker
{
    std::string imageKey = "Image";
    std::string canvasKey = "Canvas";
    int x,y, r,g,b;
    bool startedWalking;

    RandomWalker(int red, int green, int blue) : x(0), y(0), r(red), g(green), b(blue), startedWalking(false)
    {
    }

    RandomWalker() : x(0), y(0), r(-1), g(-1), b(-1), startedWalking(false) 
    {
    }

    cv::Mat operator()(LoopyFunctionInput inputs);
};
 
#endif