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
        int w = getIntParam("width");
        int h = getIntParam("height");
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
        std::string filename = inputs["file"];
        cv::Mat loadedImage = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
        int bgw = loadedImage.cols;
        int bgh = loadedImage.rows;
        int top, bottom, left, right;
        top = 0;
        bottom = 0;
        left = 0;
        right = 0;
        std::cout << bgw << " " << bgh << std::endl;
        if (inputs.count("backgroundWidth") > 0) {
            int w = inputs["backgroundWidth"];
            int border = w-bgw;
            left = border / 2;
            right = left + (border % 2);
        }

        if (inputs.count("backgroundHeight") > 0) {
            int h = inputs["backgroundHeight"];
            int border = h-bgh;
            top = border / 2;
            bottom = top + (border % 2);
        }
        cv::copyMakeBorder(loadedImage,loadedImage,top,bottom,left,right,cv::BORDER_CONSTANT,cv::Scalar(0));
        output = loadedImage;
    }
};

#endif
