#include "LoopyInputNode.h"

void LoopyInputNode::setReady()
{
    notifyReceivers();
}

void LoopyInputNode::setOutput(cv::Mat img)
{
    output = img;
}

cv::Mat ImageNode::process(LoopyFunctionInput inputs)
{
    if (currentFilename == cachedFilename &&
        (inputs.count("backgroundWidth") == 0 || getFloatParam("backgroundWidth") == cachedW) &&
        (inputs.count("backgroundHeight") == 0 || getFloatParam("backgroundHeight") == cachedH)) {
        return output;
    }
    cachedFilename = currentFilename;
    cv::Mat loadedImage = cv::imread(currentFilename, CV_LOAD_IMAGE_UNCHANGED);

    int bgw = loadedImage.cols;
    int bgh = loadedImage.rows;
    int top, bottom, left, right;
    top = 0;
    bottom = 0;
    left = 0;
    right = 0;
    std::cout << bgw << " " << bgh << std::endl;
    if (inputs.count("backgroundWidth") > 0) {
        int w = getIntParam("backgroundWidth");
        cachedW = w;
        int border = w-bgw;
        left = border / 2;
        right = left + (border % 2);

    }

    if (inputs.count("backgroundHeight") > 0) {
        int h = getIntParam("backgroundHeight");
        cachedH = h;
        int border = h-bgh;
        top = border / 2;
        bottom = top + (border % 2);
    }
    cv::copyMakeBorder(loadedImage,loadedImage,top,bottom,left,right,cv::BORDER_CONSTANT,cv::Scalar(0));
    output = loadedImage;
}