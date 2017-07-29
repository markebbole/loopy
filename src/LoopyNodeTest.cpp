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

    // Load files, etc. don't worry about this too much.
    cv::Mat image;
    cv::Mat newSrc(image.size(), CV_MAKE_TYPE(image.type(), 4));
    int from_to[] = { 0,0, 1,1, 2,2, 2,3 };
    cv::mixChannels(&image,1,&newSrc,1,from_to,4);

    // Set up functions

    // This is a function that just generates a randomly colored pixel with probability 0.05 on every pixel.
    SpeckledNoise noiseFunction(0.05, true);

    // This is a function that adds two inputs together.
    AdditionFunction ISaidIDoNotCareAboutButtsButIDo(.95);

    //These functions scale an input in the x and y direction as specified, with a center
    LinearTransformationFunction s1 = LinearTransformationFunction::Scale(1.2, .9, image.cols/2, image.rows/2);
    LinearTransformationFunction s2 = LinearTransformationFunction::Scale(1.3, 1.5, image.cols/2+100, image.rows/2+100);

    // Multiply two inputs together componentwise (so two input pixels with color (100, 50, 50) and (2, 1, 1) would result in a pixel with color (200, 50, 50))
    MultiplyFunction mult;

    // Add functions to nodes. Just make some new nodes and then set their functions to the above ones.
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
    
    LoopyNode *multiplyNode = new LoopyNode();
        multiplyNode->setProcessFunction(mult);
    
    // Connect nodes to eachother. blah.somethingKey is like the name of a parameter that the functions use internally. 
    // So for example the connection below makes it so that the noise node takes the testImage as input and assigns it to
    // the noise function's imageKey. 
    // Also, the boolean value indicates whether noiseNode should wait for the input of testImage on the FIRST iteration through the graph.
    // You might want to set this to false to break loops that would never get resolved otherwise.
    noiseNode->addInput(InputConnection(testImage, noiseFunction.imageKey, true));

    noiseNode2->addInput(InputConnection(testImage, noiseFunction.imageKey, true));

    addNode->addInput(InputConnection(noiseNode, ISaidIDoNotCareAboutButtsButIDo.foregroundKey, true));

    // For example, here the boolean is false because addNode is connected to scaleUp, and scaleUp is connected to addNode.
    // If you tried to run this graph with all booleans true then nothing would happen because the functions would be waiting for
    // input from eachother.
    addNode->addInput(InputConnection(scaleUp, ISaidIDoNotCareAboutButtsButIDo.backgroundKey, false));

    addNode2->addInput(InputConnection(noiseNode2, ISaidIDoNotCareAboutButtsButIDo.foregroundKey, true));
    addNode2->addInput(InputConnection(scaleUp2, ISaidIDoNotCareAboutButtsButIDo.backgroundKey, false));

    scaleUp->addInput(InputConnection(addNode, s1.imageInput, true));
    scaleUp2->addInput(InputConnection(addNode2, s2.imageInput, true));

    multiplyNode->addInput(InputConnection(addNode, mult.backgroundKey, true));
    multiplyNode->addInput(InputConnection(addNode2, mult.foregroundKey, true));

    // On every key press run an iteration through the graph.
    while (true) {
        testImage->setReady();

        cv::imshow( "Display window", multiplyNode->getOutput() );
        cv::waitKey(0);
    }
}
