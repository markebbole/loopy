#include "BasicLoopyFunctions.h"

#include <stdlib.h>

cv::Mat BinaryFunction::operator()(LoopyFunctionInput inputs)
{
	if (inputs.count(firstKey) == 0) {
	    return inputs[secondKey]->getOutput();
	}

	if (inputs.count(secondKey) == 0) {
		return inputs[firstKey]->getOutput();
	}

	// Iterate through back layer and add the new image on top of it.
	const cv::Mat& first = inputs[firstKey]->getOutput();
	const cv::Mat& second = inputs[secondKey]->getOutput();

	int maxR = MAX(first.rows, second.rows);
	int maxC = MAX(first.cols, second.cols);

	cv::Mat output = cv::Mat(maxR, maxC, first.type());

	for (int r = 0; r < maxR; ++r) {
		for (int c = 0; c < maxC; ++c) {
			cv::Vec4b firstPoint = (r >= first.rows || c >= first.cols) ? cv::Vec4b(0, 0, 0, 0) : first.at<cv::Vec4b>(r,c);
			cv::Vec4b secondPoint = (r >= second.rows || c >= second.cols) ? cv::Vec4b(0, 0, 0, 0) : second.at<cv::Vec4b>(r,c);
			output.at<cv::Vec4b>(r,c) = (*op)(firstPoint, secondPoint);
		}
	}

	return output;
}

cv::Mat SpeckledNoise::operator()(LoopyFunctionInput inputs)
{
	const cv::Mat& image = inputs[imageKey]->getOutput();
	cv::Mat newImage = cv::Mat(image.rows, image.cols, image.type());
	for (int r = 0; r < image.rows; r ++) {
	    for(int c = 0; c < image.cols; ++c) {
	    	float diceroll = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	    	bool isNoise = diceroll < speckleFrequency;
	    	int roll1 = rand()%256;
	    	newImage.at<cv::Vec4b>(r,c) = isNoise ? (colored ? cv::Vec4b(rand()%256, rand()%256, rand()%256, 1) :
	    		                                                cv::Vec4b(roll1, roll1, roll1))
	    		                                   : cv::Vec4b(0,0,0);
	    }
	}

	return newImage;
}

