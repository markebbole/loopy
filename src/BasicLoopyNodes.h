#ifndef BASIC_LOOPY_NODES
#define BASIC_LOOPY_NODES

#include "LoopyNode.h"

#include <stdlib.h>
#include "LinearTransformations.h"
#include "BinaryPixelOperators.h"

/**
 * This file contains some basic LoopyNodes that I feel will be useful for lots of situations.
 */

struct BinaryNode : public LoopyNode
{
public:
    std::string firstKey;
    std::string secondKey;
    BinaryPixelOperator* op;

    BinaryNode(BinaryPixelOperator* op, std::string f, std::string s) : LoopyNode()
    {
        this->firstKey = f;
        this->secondKey = s;
        this->op = op;
    }

    BinaryNode(BinaryPixelOperator* op) : BinaryNode(op, "", "")
    {
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
};

struct SpeckledNoiseNode : public LoopyNode
{
    std::string imageKey = "Image";
    float speckleFrequency;
    bool colored;

    SpeckledNoiseNode(float speckleFrequency, bool colored) : LoopyNode() {
        this->speckleFrequency = speckleFrequency;
        this->colored = colored;
    }
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

/**
 * Draw a white circle
 */
struct CircleNode : public LoopyNode
{
    std::string backgroundKey = "Background";
    int x,y;
    float radius;
    CircleNode(int x, int y, float radius) : LoopyNode()
    {
        this->x = x;
        this->y = y;
        this->radius = radius;
    }
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

#endif