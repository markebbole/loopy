#include "BasicLoopyFunctions.h"

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

cv::Mat AdditionFunction::operator()(LoopyFunctionInput inputs)
{
	if (inputs.count(foregroundKey) == 0) {
	    return inputs[backgroundKey]->getOutput();
	}

	// Iterate through back layer and add the new image on top of it.
	const cv::Mat& background = inputs[backgroundKey]->getOutput();
	const cv::Mat& foreground = inputs[foregroundKey]->getOutput();

	cv::Mat output = cv::Mat(background.rows, background.cols, background.type());

	for (int r = 0; r < background.rows; r ++) {
	    for(int c = 0; c < background.cols; ++c) {
	        cv::Vec4b bg = background.at<cv::Vec4b>(r,c);
	        cv::Vec4b fg = foreground.at<cv::Vec4b>(r,c);

	        if (fg[3] == 0) {
	        	output.at<cv::Vec4b>(r,c) = bg;
	        } else {
	        	output.at<cv::Vec4b>(r,c) = foregroundMultiplier * fg + (1-foregroundMultiplier) * bg;
	        }
	    }
	}

	return output;
}