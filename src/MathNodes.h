#ifndef MATH_NODES
#define MATH_NODES

#include "BasicLoopyNodes.h"

// might be better to just make these static Nodes that construct a binaryNode with the right operator?
// also, wow I want to eventually do something better than arbitrary strings for keys.
struct AdditionNode : public BinaryNode
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    AdditionNode(float foregroundMultiplier) : BinaryNode(new AddPixelOperator(foregroundMultiplier))
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }

    AdditionNode() : AdditionNode(1)
    {
    }
};

struct AdditionModNode : public BinaryNode
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    AdditionModNode() : BinaryNode(new AddPixelModOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct MultiplyNode : public BinaryNode
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    MultiplyNode() : BinaryNode(new MultiplyPixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct SubtractionNode : public BinaryNode
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    SubtractionNode() : BinaryNode(new SubtractPixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

struct DivideNode : public BinaryNode
{
    std::string foregroundKey = "F";
    std::string backgroundKey = "B";
    DivideNode() : BinaryNode(new DividePixelOperator())
    {
        firstKey = foregroundKey;
        secondKey = backgroundKey;
    }
};

#endif