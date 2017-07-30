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
public:
    std::string firstKey;
    std::string secondKey;
    BinaryPixelOperator* op;

    BinaryFunction(BinaryPixelOperator* op, std::string f, std::string s) : op(op), firstKey(f), secondKey(s)
    {
    }

    BinaryFunction(BinaryPixelOperator* op) : BinaryFunction(op, "", "")
    {
    }

    cv::Mat operator()(LoopyFunctionInput inputs);
};

// might be better to just make these static functions that construct a binaryfunction with the right operator?
struct AdditionFunction : public BinaryFunction
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
	AdditionFunction(float foregroundMultiplier) : BinaryFunction(new AddPixelOperator(foregroundMultiplier)) 
	{
        firstKey = foregroundKey;
        secondKey = backgroundKey;
	}
};

struct AdditionModFunction : public BinaryFunction
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    AdditionModFunction() : BinaryFunction(new AddPixelModOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct MultiplyFunction : public BinaryFunction
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    MultiplyFunction() : BinaryFunction(new MultiplyPixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct SubtractionFunction : public BinaryFunction
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    SubtractionFunction() : BinaryFunction(new SubtractPixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct DivideFunction : public BinaryFunction
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    DivideFunction() : BinaryFunction(new DividePixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
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

/**
 * Draw a white circle
 */
struct CircleFunction
{
    std::string backgroundKey = "Background";
    int x,y;
    float radius;
    CircleFunction(int x, int y, float radius) : x(x), y(y), radius(radius)
    {
    }
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