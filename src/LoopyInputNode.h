#ifndef LOOPY_INPUT_NODE
#define LOOPY_INPUT_NODE

#include "LoopyNode.h"
#include <string>

using namespace std;
class LoopyInputNode : public LoopyNode
{

public:

	/**
	 * Since this node doesn't depend on any inputs this is a method that 
	 * notifies all child nodes that output is ready.
	 */
    virtual void setReady();

    void setOutput(cv::Mat img);

    LoopyInputNode(std::string outputKey) : LoopyNode(outputKey)
    {
    }

    LoopyInputNode() : LoopyInputNode(std::to_string(LoopyNode::nextId++))
    {
    }

};

class LoopyNumberNode : public LoopyInputNode
{
public:
    LoopyNumberNode(std::string outputKey) : LoopyInputNode(outputKey)
    {
        output = cv::Mat::zeros(1, 1, CV_32F);
    }

    LoopyNumberNode() : LoopyNumberNode(std::to_string(LoopyNode::nextId++))
    {
    }

    void setOutput(float number) {
        output.at<float>(0, 0) = number;
    }
};

class TickerNode : public LoopyInputNode
{
public:
    TickerNode(std::string outputKey) : LoopyInputNode(outputKey)
    {
        output = cv::Mat::zeros(1, 1, CV_32F);
    }

    TickerNode() : TickerNode(std::to_string(LoopyNode::nextId++))
    {
    }
    void setOutput(float number) {
        output.at<float>(0, 0) = number;
    }

    virtual void setReady()
    {
        LoopyInputNode::setReady();
        output.at<float>(0, 0) = output.at<float>(0, 0) + 1;
    }
};

#endif
