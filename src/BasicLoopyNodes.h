#ifndef BASIC_LOOPY_NODES
#define BASIC_LOOPY_NODES

#include "LoopyNode.h"

#include <stdlib.h>
#include "LinearTransformations.h"
#include "BinaryPixelOperators.h"

using namespace std;

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

class ImageNode : public LoopyNode
{
    int cachedW;
    int cachedH;
    string cachedFilename;
    string currentFilename;
public:

    ImageNode(std::string outputKey) : LoopyNode(outputKey)
    {
        cachedW = 0;
        cachedH = 0;
        cachedFilename = "";
    }

    ImageNode() : ImageNode(std::to_string(LoopyNode::nextId++))
    {
    }

    void setFileName(string filename)
    {
        currentFilename = filename;
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
};

class TickerNode : public LoopyNode
{
public:

    TickerNode(std::string outputKey) : LoopyNode(outputKey)
    {
        output = cv::Mat::zeros(1, 1, CV_32F);
    }

    TickerNode() : TickerNode(std::to_string(LoopyNode::nextId++))
    {
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
};

class SineNode : public LoopyNode
{
public:

    SineNode(std::string outputKey) : LoopyNode(outputKey)
    {
        output = cv::Mat::zeros(1, 1, CV_32F);
    }

    SineNode() : SineNode(std::to_string(LoopyNode::nextId++))
    {
    }

    virtual cv::Mat process(LoopyFunctionInput inputs);
};

#endif
