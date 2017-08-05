#ifndef MATH_NODES
#define MATH_NODES

#include "BasicLoopyNodes.h"

//note: make a subclass of BinaryNode called ForegroundBackgroundNode or something.
//Then all these guys can make one of those with their binary operator

// might be better to just make these static Nodes that construct a binaryNode with the right operator?
// also, wow I want to eventually do something better than arbitrary strings for keys.
struct AdditionNode : public BinaryNode
{
    std::string foregroundKey = "foregroundKey";
    std::string backgroundKey = "backgroundKey";
    AdditionNode(float foregroundMultiplier) : BinaryNode(new AddPixelOperator(foregroundMultiplier))
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }

    AdditionNode() : AdditionNode(1)
    {
    }

    virtual void setFunctionInputs(json inputs) {
        BinaryNode::setFunctionInputs(inputs);
        float foregroundMultiplier = inputs.count("foregroundMultiplier") > 0 ? (float)inputs["foregroundMultiplier"] : 1;
        op = new AddPixelOperator(foregroundMultiplier);
    }
};

struct AdditionModNode : public BinaryNode
{
    std::string foregroundKey = "foregroundKey";
    std::string backgroundKey = "backgroundKey";
    AdditionModNode() : BinaryNode(new AddPixelModOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct MultiplyNode : public BinaryNode
{
    std::string foregroundKey = "foregroundKey";
    std::string backgroundKey = "backgroundKey";
    MultiplyNode() : BinaryNode(new MultiplyPixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct SubtractionNode : public BinaryNode
{
    std::string foregroundKey = "foregroundKey";
    std::string backgroundKey = "backgroundKey";
    SubtractionNode() : BinaryNode(new SubtractPixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct DivideNode : public BinaryNode
{
    std::string foregroundKey = "foregroundKey";
    std::string backgroundKey = "backgroundKey";
    DivideNode() : BinaryNode(new DividePixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

#endif