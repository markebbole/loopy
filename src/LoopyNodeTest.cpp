#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "BasicLoopyFunctions.h"
#include "LinearTransformations.h"

int main()
{
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.

    // Load files, etc
    cv::Mat image;
    image = cv::imread("man-table-fish.jpg", CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat image2;
    image2 = cv::imread("doggo.png", CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat newSrc(image.size(), CV_MAKE_TYPE(image.type(), 4));
    int from_to[] = { 0,0, 1,1, 2,2, 2,3 };
    cv::mixChannels(&image,1,&newSrc,1,from_to,4);

    // Set up functions
    SpeckledNoise noiseFunction(0.01, true);
    AdditionFunction ISaidIDoNotCareAboutButtsButIDo(1);
    LinearTransformationFunction s = LinearTransformationFunction::Scale(1.01, 1.01, image.cols/2, image.rows/2);

    // Add functions to nodes
    LoopyInputNode *testImage = new LoopyInputNode();
        testImage->setOutput(newSrc);
    LoopyNode *noiseNode = new LoopyNode();
        noiseNode->setProcessFunction(noiseFunction);
    LoopyNode *addNode = new LoopyNode();
        addNode->setProcessFunction(ISaidIDoNotCareAboutButtsButIDo);
    LoopyNode *scaleUp = new LoopyNode();
        scaleUp->setProcessFunction(s);
    
    // Connect nodes to eachother
    noiseNode->addInput(InputConnection(testImage, noiseFunction.imageKey, true));

    addNode->addInput(InputConnection(noiseNode, ISaidIDoNotCareAboutButtsButIDo.backgroundKey, true));
    addNode->addInput(InputConnection(scaleUp, ISaidIDoNotCareAboutButtsButIDo.foregroundKey, false));

    scaleUp->addInput(InputConnection(addNode, s.imageInput, true));

    // On every key press run an iteration through the graph.
    while (true) {
        testImage->setReady();

        cv::imshow( "Display window", addNode->getOutput() );
        cv::waitKey(0);
    }
}
