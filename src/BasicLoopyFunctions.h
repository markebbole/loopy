#ifndef BASIC_LOOPY_FUNCTIONS
#define BASIC_LOOPY_FUNCTIONS

#include "LoopyNode.h"

#include <stdlib.h>
#include "LinearTransformations.h"
#include "BinaryPixelOperators.h"

/**
 * This file contains some basic LoopyFunctions that I feel will be useful for lots of situations.
 */

struct BinaryFunction : public LoopyNode
{
public:
    std::string firstKey;
    std::string secondKey;
    BinaryPixelOperator* op;

    BinaryFunction(BinaryPixelOperator* op, std::string f, std::string s) : LoopyNode()
    {
        this->firstKey = f;
        this->secondKey = s;
        this->op = op;
    }

    BinaryFunction(BinaryPixelOperator* op) : BinaryFunction(op, "", "")
    {
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
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

struct SpeckledNoise : public LoopyNode
{
    std::string imageKey = "Image";
    float speckleFrequency;
    bool colored;

    SpeckledNoise(float speckleFrequency, bool colored) : LoopyNode() {
        this->speckleFrequency = speckleFrequency;
        this->colored = colored;
    }
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

/**
 * Draw a white circle
 */
struct CircleFunction : public LoopyNode
{
    std::string backgroundKey = "Background";
    int x,y;
    float radius;
    CircleFunction(int x, int y, float radius) : LoopyNode()
    {
        this->x = x;
        this->y = y;
        this->radius = radius;
    }
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

// struct RandomWalker : public LoopyNode
// {
//     std::string imageKey = "Image";
//     std::string canvasKey = "Canvas";
//     int x,y, r,g,b;
//     bool startedWalking;

//     RandomWalker(int red, int green, int blue) : x(0), y(0), r(red), g(green), b(blue), startedWalking(false)
//     {
//     }

//     RandomWalker() : x(0), y(0), r(-1), g(-1), b(-1), startedWalking(false) 
//     {
//     }

//     virtual cv::Mat process(LoopyFunctionInput inputs);
// };
 
#endif