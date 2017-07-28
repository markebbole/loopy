#ifndef LOOPY_INPUT_NODE
#define LOOPY_INPUT_NODE

#include "LoopyNode.h"

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

#endif
