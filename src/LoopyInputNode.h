#ifndef LOOPY_INPUT_NODE
#define LOOPY_INPUT_NODE

#include "LoopyNode.h"
#include <string>
class LoopyInputNode : public LoopyNode
{

public:

	/**
	 * Since this node doesn't depend on any inputs this is a method that 
	 * notifies all child nodes that output is ready.
	 */
    void setReady();

    void setOutput(cv::Mat img);

    LoopyInputNode(std::string outputKey) : LoopyNode(outputKey)
    {
    }

    LoopyInputNode() : LoopyInputNode(std::to_string(LoopyNode::nextId++))
    {
    }

};

class ClearImageNode : public LoopyInputNode
{
public:

    ClearImageNode(std::string outputKey) : LoopyInputNode(outputKey)
    {
    }

    ClearImageNode() : ClearImageNode(std::to_string(LoopyNode::nextId++))
    {
    }

    virtual void setFunctionInputs(json inputs) {
        LoopyNode::setFunctionInputs(inputs);
        std::cout << inputs << std::endl;
        int w = inputs["width"];
        int h = inputs["height"];
        output = cv::Mat::zeros(h, w, CV_8UC4);
    }
};

class ImageNode : public LoopyInputNode
{
public:

    ImageNode(std::string outputKey) : LoopyInputNode(outputKey)
    {
    }

    ImageNode() : ImageNode(std::to_string(LoopyNode::nextId++))
    {
    }

    virtual void setFunctionInputs(json inputs) {
        LoopyNode::setFunctionInputs(inputs);
        std::cout << inputs << std::endl;
        std::string filename = inputs["file"];
        output = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
    }
};

#endif
