#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "BasicLoopyFunctions.h"
#include "LinearTransformations.h"

void noisy_test()
{
    cv::Mat image;
    image = cv::imread("man-table-fish.jpg", CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat newSrc(image.size(), CV_MAKE_TYPE(image.type(), 4));
    int from_to[] = { 0,0, 1,1, 2,2, 2,3 };
    cv::mixChannels(&image,1,&newSrc,1,from_to,4);


    //Set up functions

    // This is a function that just generates a randomly colored pixel with probability 0.05 on every pixel.
    SpeckledNoise *noiseNode = new SpeckledNoise(0.05, true);
    SpeckledNoise *noiseNode2 = new SpeckledNoise(0.05, true);

    // This is a function that adds two inputs together.
    AdditionFunction *addNode = new AdditionFunction(.95);
    AdditionFunction *addNode2 = new AdditionFunction(.95);

    //These functions scale an input in the x and y direction as specified, with a center
    LinearTransformationNode *scaleUp = LinearTransformationNode::Scale(1.2, .9, image.cols/2, image.rows/2);
    LinearTransformationNode *scaleUp2 = LinearTransformationNode::Scale(3, 3, image.cols/2+100, image.rows/2+100);

    // Multiply two inputs together componentwise (so two input pixels with color (100, 50, 50) and (2, 1, 1) would result in a pixel with color (200, 50, 50))
    MultiplyFunction *multiplyNode = new MultiplyFunction();

    // Add functions to nodes. Just make some new nodes and then set their functions to the above ones.
    LoopyInputNode *testImage = new LoopyInputNode();
        testImage->setOutput(newSrc);

    
    // Connect nodes to eachother. blah.somethingKey is like the name of a parameter that the functions use internally. 
    // So for example the connection below makes it so that the noise node takes the testImage as input and assigns it to
    // the noise function's imageKey. 
    // Also, the boolean value indicates whether noiseNode should wait for the input of testImage on the FIRST iteration through the graph.
    // You might want to set this to false to break loops that would never get resolved otherwise.
    noiseNode->addInput(testImage, noiseNode->imageKey, true);

    noiseNode2->addInput(testImage, noiseNode->imageKey, true);

    addNode->addInput(noiseNode, addNode->foregroundKey, true);

    // For example, here the boolean is false because addNode is connected to scaleUp, and scaleUp is connected to addNode.
    // If you tried to run this graph with all booleans true then nothing would happen because the functions would be waiting for
    // input from eachother.
    addNode->addInput(scaleUp, addNode->backgroundKey, false);

    addNode2->addInput(noiseNode2, addNode->foregroundKey, true);
    addNode2->addInput(scaleUp2, addNode->backgroundKey, false);

    scaleUp->addInput(addNode, scaleUp->imageInput, true);
    scaleUp2->addInput(addNode2, scaleUp2->imageInput, true);

    multiplyNode->addInput(addNode, multiplyNode->backgroundKey, true);
    multiplyNode->addInput(addNode2, multiplyNode->foregroundKey, true);

    // On every key press run an iteration through the graph.
    while (true) {
        testImage->setReady();

        cv::imshow( "Display window", multiplyNode->getOutput() );
        cv::waitKey(0);
    }
}

void circle_test()
{
    // Load files, etc. don't worry about this too much.
    cv::Mat image;
    image = cv::imread("phone_screen_360x640.png", CV_LOAD_IMAGE_UNCHANGED);

    LoopyInputNode *testImage = new LoopyInputNode();
        testImage->setOutput(image);
    CircleFunction *circleNode = new CircleFunction(image.cols/2, image.rows/2, 20);
    LinearTransformationNode *scaleNode = LinearTransformationNode::Scale(1.1, 1.1, image.cols/2, image.rows/2);
    AdditionFunction *addNode = new AdditionFunction(0.8);
    SpeckledNoise *noiseNode = new SpeckledNoise(0.001, false);
    AdditionModFunction *addModNode = new AdditionModFunction();
    LinearTransformationNode *scale2 = LinearTransformationNode::Scale(1.5, 1.5, image.cols/2+50, image.rows/2);

    circleNode->addInput(noiseNode, circleNode->backgroundKey, true);

    scaleNode->addInput(addNode, scaleNode->imageInput, true);

    addNode->addInput(scaleNode, addNode->foregroundKey, false);
    addNode->addInput(circleNode, addNode->backgroundKey, true);

    noiseNode->addInput(testImage, noiseNode->imageKey, true);

    scale2->addInput(addModNode, scale2->imageInput, true);

    addModNode->addInput(scale2, addModNode->foregroundKey, false);
    addModNode->addInput(addNode, addModNode->backgroundKey, true);

    while (true) {
        testImage->setReady();
        cv::imshow( "Display window", addModNode->getOutput() );
        cv::waitKey(0);
    }
}

int main()
{
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.

    // Load files, etc. don't worry about this too much.
    //circle_test();
    noisy_test();

}
