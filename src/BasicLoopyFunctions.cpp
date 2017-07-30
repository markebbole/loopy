#include "BasicLoopyFunctions.h"

cv::Mat BinaryFunction::process(LoopyFunctionInput inputs)
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

cv::Mat SpeckledNoise::process(LoopyFunctionInput inputs)
{
	const cv::Mat& image = inputs[imageKey]->getOutput();
	cv::Mat newImage = cv::Mat(image.rows, image.cols, image.type());
	for (int r = 0; r < image.rows; r ++) {
	    for(int c = 0; c < image.cols; ++c) {
	    	float diceroll = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	    	bool isNoise = diceroll < speckleFrequency;
	    	int roll1 = rand()%256;
	    	newImage.at<cv::Vec4b>(r,c) = isNoise ? (colored ? cv::Vec4b(rand()%256, rand()%256, rand()%256, 255) :
	    		                                               cv::Vec4b(roll1, roll1, roll1))
	    	                                      : cv::Vec4b(0,0,0);
	    }
	}

	return newImage;
};

cv::Mat CircleFunction::process(LoopyFunctionInput inputs)
{
	const cv::Mat& background = inputs[backgroundKey]->getOutput();
	const int numCircleIterations = 300;
	cv::Mat newImage = background.clone();
	double angleChange = 2.0 * CV_PI / numCircleIterations;
	double angle = 0;
	for (int i = 0; i < numCircleIterations; ++i)
	{
		int x_ = std::floor(x + radius * cos(angle));
		int y_ = std::floor(y + radius * sin(angle));

		x_ = MIN(MAX(x_, 0), background.cols-1);
		y_ = MIN(MAX(y_, 0), background.rows-1);
		newImage.at<cv::Vec4b>(y_, x_) = cv::Vec4b(255, 255, 255, 255);
		angle += angleChange;
	}

	return newImage;
}

/**
 * 0 1 2
 * 7   3
 * 6 5 4
*/
// cv::Mat RandomWalker::process(LoopyFunctionInput inputs)
// {
	
// 	std::string keyToUse = inputs.count(imageKey) == 0 ? canvasKey : imageKey;
// 	cv::Mat image = inputs[keyToUse]->getOutput().clone();

// 	if (!startedWalking) {
// 		x = rand() % image.cols;
// 		y = rand() % image.rows;
// 		startedWalking = true;
// 	}
// 	int count = 0;
// 	int total = 130;
// 	while(count < total) {
// 		int direction = rand() % 8;
// 		if (r < 0 || g < 0 || b < 0) {
// 			image.at<cv::Vec4b>(y,x) = (r < 0 || g < 0 || b < 0) ? cv::Vec4b(rand()%256, rand()%256, rand()%256, 1) : cv::Vec4b(r, g, b, 1);
// 		}
// 		//this is so dumb
// 		x = MAX(((direction == 1 || direction == 5) ? x : (direction >= 2 && direction <= 4) ? x+1 : x-1) % image.cols, 0);
// 		y = MAX(((direction == 7 || direction == 3) ? y  : (direction >= 0 && direction <= 2) ? y-1 : y+1) % image.rows, 0);
// 		count++;
// 	}

// 	return image;
// }