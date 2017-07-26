#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

// Rotate and scale an image
struct BasicScaleAndRotateBooty
{
    float rotationDegrees;
    float scaleFactor;
    cv::Mat operator()(std::map<std::string, LoopyNode *> inputs) {
        const cv::Mat& input = inputs["ImageInput"]->getOutput();

        cv::Point2f center(input.cols/2.f, input.rows/2.f);

        cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, rotationDegrees, scaleFactor);

        cv::Mat output;
        cv::warpAffine(input, output, rotation_matrix, cv::Size(input.cols, input.rows));

        return output;
    }
};

// Add an overlay image onto a background image.
// The intensities don't have to add up to 1 because haha
struct BasicAddBooty
{
    float backgroundIntensity;
    float overlayIntensity;

    cv::Mat operator()(std::map<std::string, LoopyNode *> inputs)
    {

        if (inputs.count("Overlay") == 0) {
            return inputs["Background"]->getOutput();
        }

        // Iterate through back layer and add the new image on top of it.
        const cv::Mat& background = inputs["Background"]->getOutput();
        const cv::Mat& overlay = inputs["Overlay"]->getOutput();

        cv::Mat output = cv::Mat(background.rows, background.cols, background.type());

        for (int r = 0; r < background.rows; r ++) {
            for(int c = 0; c < background.cols; ++c) {
                cv::Vec3b p = background.at<cv::Vec3b>(r,c);

                int red = MIN(backgroundIntensity * p[0] + overlayIntensity * overlay.at<cv::Vec3b>(r, c)[0], 255);
                int green = MIN(backgroundIntensity * p[1] + overlayIntensity * overlay.at<cv::Vec3b>(r, c)[1], 255);
                int blue = MIN(backgroundIntensity * p[2] + overlayIntensity * overlay.at<cv::Vec3b>(r, c)[2], 255);

                output.at<cv::Vec3b>(r,c) = cv::Vec3b(red,green,blue);
            }
        }

        return output;
    }
};

int main()
{
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.

    LoopyInputNode *testImage = new LoopyInputNode("TestInput");

    cv::Mat image;
    image = cv::imread("doggo.jpg", CV_LOAD_IMAGE_COLOR);

    LoopyNode *scaleNode = new LoopyNode("Scale");

    BasicScaleAndRotateBooty littleBoopBop;
    littleBoopBop.rotationDegrees = 5;
    littleBoopBop.scaleFactor = 0.9;

    scaleNode->setProcessFunction(littleBoopBop);

    LoopyNode *addNode = new LoopyNode("Add");

    BasicAddBooty littleAddBaby;
    littleAddBaby.backgroundIntensity = 0.4;
    littleAddBaby.overlayIntensity = 0.7;

    addNode->setProcessFunction(littleAddBaby);

    scaleNode->addInput(InputConnection(addNode, "ImageInput", true));

    // false here means on the first iteration of the graph we don't wait for output from the scale node.
    // Otherwise we are stuck.
    addNode->addInput(InputConnection(scaleNode, "Overlay", false));

    addNode->addInput(InputConnection(testImage, "Background", true));

    testImage->setOutput(image);

    // On every key press run an iteration through the graph.
    while (true) {
        testImage->setReady();
        cv::imshow( "Display window", addNode->getOutput() );
        cv::waitKey(0);
    }
}
