#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "BasicLoopyFunctions.h"

int main()
{
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.

    LoopyInputNode *testImage = new LoopyInputNode("TestInput");

    cv::Mat image;
    image = cv::imread("frog.png", CV_LOAD_IMAGE_UNCHANGED);


    LoopyNode *scaleAndRotate = new LoopyNode("ScaleAndRotate");

    LinearTransformationFunction s = Scale(0.75, 0.75, image.cols/2, image.rows/2);
    LinearTransformationFunction r = Rotate(20, image.cols/2, image.rows/2);
    LinearTransformationFunction rs = r * s;
    scaleAndRotate->setProcessFunction(rs);

    LoopyNode *addNode = new LoopyNode("Add");

    AdditionFunction ISaidIDoNotCareAboutButtsButIDo(1);

    addNode->setProcessFunction(ISaidIDoNotCareAboutButtsButIDo);

    scaleAndRotate->addInput(InputConnection(addNode, r.imageInput, true));

    // false here means on the first iteration of the graph we don't wait for output from the scale node.
    // Otherwise we are stuck.
    addNode->addInput(InputConnection(scaleAndRotate, ISaidIDoNotCareAboutButtsButIDo.foregroundKey, false));

    addNode->addInput(InputConnection(testImage, ISaidIDoNotCareAboutButtsButIDo.backgroundKey, true));

    testImage->setOutput(image);

    // On every key press run an iteration through the graph.
    while (true) {
        testImage->setReady();
        cv::imshow( "Display window", addNode->getOutput() );
        cv::waitKey(0);
    }
}
