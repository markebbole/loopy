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
    void setReady();

    void setOutput(cv::Mat img);

    LoopyInputNode(std::string outputKey) : LoopyNode(outputKey)
    {
    }

    LoopyInputNode() : LoopyInputNode(std::to_string(LoopyNode::nextId++))
    {
    }

};

// class ClearImageNode : public LoopyInputNode
// {
// public:

//     ClearImageNode(std::string outputKey) : LoopyInputNode(outputKey)
//     {
//     }

//     ClearImageNode() : ClearImageNode(std::to_string(LoopyNode::nextId++))
//     {
//     }

//     virtual void setFunctionInputs(json inputs) {
//         LoopyNode::setFunctionInputs(inputs);
//         int w = getIntParam("width");
//         int h = getIntParam("height");
//         output = cv::Mat::zeros(h, w, CV_8UC4);
//     }
// };

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

class ImageNode : public LoopyInputNode
{
    int cachedW;
    int cachedH;
    string cachedFilename;
    string currentFilename;
public:

    ImageNode(std::string outputKey) : LoopyInputNode(outputKey)
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

#endif
