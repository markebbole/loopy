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

    BinaryNode(BinaryPixelOperator* op) : BinaryNode(op, "0", "1")
    {
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
};
 
struct SpeckledNoiseNode : public LoopyNode
{
    std::string imageKey = "imageKey";

    SpeckledNoiseNode() : LoopyNode()
    {
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
};

struct SineNode : public LoopyNode
{
    std::string imageKey = "imageKey";
    SineNode() : LoopyNode() {
    }

    void setFunctionInputs(json inputs) {
        LoopyNode::setFunctionInputs(inputs);
        functionInputs["updateWave"] = 0.0f;
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
};

/**
 * Draw a white circle
 */
struct CircleNode : public LoopyNode
{
    std::string backgroundKey = "backgroundKey";
    CircleNode() : LoopyNode()
    {
    }
    virtual cv::Mat process(LoopyFunctionInput inputs);
};

#endif