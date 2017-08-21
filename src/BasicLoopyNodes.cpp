#include "BasicLoopyNodes.h"

cv::Mat BinaryNode::process(LoopyFunctionInput inputs)
{
	if (inputs.count(firstKey) == 0) {
	    return inputs[secondKey]->getOutput();
	}

	if (inputs.count(secondKey) == 0) {
		return inputs[firstKey]->getOutput();
	}

	const cv::Mat& first = inputs[firstKey]->getOutput();
	const cv::Mat& second = inputs[secondKey]->getOutput();

	int maxR = MAX(first.rows, second.rows);
	int maxC = MAX(first.cols, second.cols);

	cv::Mat output = cv::Mat(maxR, maxC, first.type());

	float f = inputs.count("foregroundMultiplier") > 0 ? getFloatParam("foregroundMultiplier") : 1;
	float b = inputs.count("backgroundMultiplier") > 0 ? getFloatParam("backgroundMultiplier") : (1 - foregroundMultiplier);

	for (int r = 0; r < maxR; ++r) {
		for (int c = 0; c < maxC; ++c) {
			cv::Vec4b firstPoint = (r >= first.rows || c >= first.cols) ? cv::Vec4b(0, 0, 0, 0) : first.at<cv::Vec4b>(r,c);
			cv::Vec4b secondPoint = (r >= second.rows || c >= second.cols) ? cv::Vec4b(0, 0, 0, 0) : second.at<cv::Vec4b>(r,c);
			output.at<cv::Vec4b>(r,c) = (*op)(firstPoint, secondPoint, f, b);
		}
	}

	return output;
}

cv::Mat SpeckledNoiseNode::process(LoopyFunctionInput inputs)
{
	const cv::Mat& image = inputs[imageKey]->getOutput();
	cv::Mat newImage = cv::Mat(image.rows, image.cols, image.type());
	float speckleFrequency = getFloatParam("speckleFrequency");
	bool colored = getBoolParam("colored");
	for (int r = 0; r < image.rows; ++r) {
	    for(int c = 0; c < image.cols; ++c) {
	    	float diceroll = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	    	bool isNoise = diceroll < speckleFrequency;
	    	int roll1 = rand() % 256;
	    	newImage.at<cv::Vec4b>(r,c) = isNoise ? (colored ? cv::Vec4b(rand() % 256, rand() % 256, rand() % 256, 255) :
	    		                                               cv::Vec4b(roll1, roll1, roll1, 255))
	    	                                      : cv::Vec4b(0, 0, 0);
	    }
	}

	return newImage;
};

// cv::Mat SineNode::process(LoopyFunctionInput inputs)
// {
// 	const cv::Mat& image = inputs[imageKey]->getOutput();
// 	cv::Mat newImage = cv::Mat(image.rows, image.cols, image.type());

// 	float waveDiff = getFloatParam("waveDiff");
//     float frequency = getFloatParam("frequency");
//     float updateWave = getFloatParam("updateWave");
//     float red = getFloatParam("red");
//     float green = getFloatParam("green");
//     float blue = getFloatParam("blue");

// 	int pixelCounter = 0;
// 	int norm = image.rows * image.cols;
// 	for (int r = 0; r < image.rows; ++r) {
// 	    for(int c = 0; c < image.cols; ++c) {
// 	    	float s = (1 + sin(updateWave + frequency*pixelCounter)) / 2;
// 	    	newImage.at<cv::Vec4b>(r,c) = cv::Vec4b(blue + s * 150, green, red + 70 * sqrt(s), 255);
// 	    }
// 	    pixelCounter++;
	    

// 	}
// 	//functionInputs["updateWave"] = updateWave + waveDiff;

	
// 	return newImage;
// }
