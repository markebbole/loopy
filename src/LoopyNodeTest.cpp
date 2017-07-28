#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "BasicLoopyFunctions.h"
#include "LinearTransformations.h"


void setupWalker(LoopyNode *walkerNode, LoopyNode *input)
{
    RandomWalker walker;
    LinearTransformationFunction scale = LinearTransformationFunction::Translate(-20, 20);

    LoopyNode *scaleNode = new LoopyNode();
        scaleNode->setProcessFunction(scale);

    walkerNode->setProcessFunction(walker);

    walkerNode->addInput(InputConnection(scaleNode, walker.imageKey, false));
    walkerNode->addInput(InputConnection(input, walker.canvasKey, true));

    scaleNode->addInput(InputConnection(walkerNode, scale.imageInput, true));

}

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
    SpeckledNoise noiseFunction(0.0, true);
    AdditionFunction ISaidIDoNotCareAboutButtsButIDo(.95);
    LinearTransformationFunction s1 = LinearTransformationFunction::Scale(1.3, 1.8, image.cols/2, image.rows/2);
    LinearTransformationFunction s2 = LinearTransformationFunction::Scale(2.2, 1.2, image.cols/2+100, image.rows/2+100);
    MultiplyFunction mult;

    // Add functions to nodes
    LoopyInputNode *testImage = new LoopyInputNode();
        testImage->setOutput(newSrc);
    LoopyNode *noiseNode = new LoopyNode();
        noiseNode->setProcessFunction(noiseFunction);
    LoopyNode *noiseNode2 = new LoopyNode();
        noiseNode2->setProcessFunction(noiseFunction);
    LoopyNode *addNode = new LoopyNode();
        addNode->setProcessFunction(ISaidIDoNotCareAboutButtsButIDo);
    LoopyNode *addNode2 = new LoopyNode();
        addNode2->setProcessFunction(ISaidIDoNotCareAboutButtsButIDo);
    LoopyNode *scaleUp = new LoopyNode();
        scaleUp->setProcessFunction(s1);
    LoopyNode *scaleUp2 = new LoopyNode();
        scaleUp2->setProcessFunction(s2);
    LoopyNode *randWalker = new LoopyNode();
    

    // LoopyNode *multiplyNode = new LoopyNode();
    //     multiplyNode->setProcessFunction(mult);
    
    // // Connect nodes to eachother
    noiseNode->addInput(InputConnection(testImage, noiseFunction.imageKey, true));
    // noiseNode2->addInput(InputConnection(testImage, noiseFunction.imageKey, true));

    // addNode->addInput(InputConnection(noiseNode, ISaidIDoNotCareAboutButtsButIDo.foregroundKey, true));
    // addNode->addInput(InputConnection(scaleUp, ISaidIDoNotCareAboutButtsButIDo.backgroundKey, false));

    // addNode2->addInput(InputConnection(noiseNode2, ISaidIDoNotCareAboutButtsButIDo.foregroundKey, true));
    // addNode2->addInput(InputConnection(scaleUp2, ISaidIDoNotCareAboutButtsButIDo.backgroundKey, false));

    // scaleUp->addInput(InputConnection(addNode, s1.imageInput, true));
    // scaleUp2->addInput(InputConnection(addNode2, s2.imageInput, true));

    // multiplyNode->addInput(InputConnection(addNode, mult.backgroundKey, true));
    // multiplyNode->addInput(InputConnection(addNode2, mult.foregroundKey, true));

    // On every key press run an iteration through the graph.
    setupWalker(randWalker, noiseNode);
    while (true) {
        testImage->setReady();

        cv::imshow( "Display window", randWalker->getOutput() );
        cv::waitKey(0);
    }
}
