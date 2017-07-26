#include "LoopyInputNode.h"

void LoopyInputNode::setReady() {
    notifyReceivers();
}

void LoopyInputNode::setOutput(cv::Mat img) {
    output = img;
}
