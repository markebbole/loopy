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

    cv::Mat image;
    image = cv::imread("man-table-fish.jpg", CV_LOAD_IMAGE_UNCHANGED);

    cv::Mat image2;
    image2 = cv::imread("doggo.png", CV_LOAD_IMAGE_UNCHANGED);

    cv::Mat newSrc(image.size(), CV_MAKE_TYPE(image.type(), 4));

    int from_to[] = { 0,0, 1,1, 2,2, 2,3 };

    cv::mixChannels(&image,1,&newSrc,1,from_to,4);

    LoopyInputNode *testImage = new LoopyInputNode();
    LoopyInputNode *dogImage = new LoopyInputNode();

    testImage->setOutput(newSrc);
    dogImage->setOutput(newSrc);

    LoopyNode *dogSpeckles = new LoopyNode();
    SpeckledNoise noise(0.01, true);
    dogSpeckles->setProcessFunction(noise);

    dogSpeckles->addInput(InputConnection(testImage, noise.imageKey, true));

    LoopyNode *addNode = new LoopyNode();
    AdditionFunction ISaidIDoNotCareAboutButtsButIDo(1);
    addNode->setProcessFunction(ISaidIDoNotCareAboutButtsButIDo);
    addNode->addInput(InputConnection(dogSpeckles, ISaidIDoNotCareAboutButtsButIDo.backgroundKey, true));

    LoopyNode *scaleAndRotate = new LoopyNode();

    LinearTransformationFunction rs = LinearTransformationFunction::Scale(1.01, 1.01, image.cols/2, image.rows/2);
    //LinearTransformationFunction r = Translate(100, 5);
    //LinearTransformationFunction rs = r*s;
    scaleAndRotate->setProcessFunction(rs);
    scaleAndRotate->addInput(InputConnection(addNode, rs.imageInput, true));
    addNode->addInput(InputConnection(scaleAndRotate, ISaidIDoNotCareAboutButtsButIDo.foregroundKey, false));

    // On every key press run an iteration through the graph.
    while (true) {
        testImage->setReady();
        dogImage->setReady();

        cv::imshow( "Display window", addNode->getOutput() );
        cv::waitKey(0);
    }
}
