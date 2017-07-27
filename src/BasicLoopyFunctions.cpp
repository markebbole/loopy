#include "BasicLoopyFunctions.h"

#include <stdlib.h>

cv::Mat LinearTransformationFunction::operator()(LoopyFunctionInput inputs)
{
	const cv::Mat& input = inputs[imageInput]->getOutput();

	cv::Mat output;
    cv::warpPerspective(input, output, transform_3x3, cv::Size(input.cols, input.rows));
    return output;
}

LinearTransformationFunction::LinearTransformationFunction(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	float data[9] = {a, b, c,
		             d, e, f,
		             g, h, i};

	transform_3x3 = cv::Mat(3, 3, CV_32F, data).clone();
}

LinearTransformationFunction LinearTransformationFunction::inverse()
{
	LinearTransformationFunction t;
	t.transform_3x3 = this->transform_3x3.inv();
	return t;
}

LinearTransformationFunction LinearTransformationFunction::operator*(const LinearTransformationFunction &a)
{
	LinearTransformationFunction t;
	t.transform_3x3 = transform_3x3 * a.transform_3x3;
	return t;
}

std::string AdditionFunction::foregroundKey = "F";
std::string AdditionFunction::backgroundKey = "B";

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

