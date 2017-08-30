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

	float f = getFloatParam("foregroundMultiplier", 1);
	float b = getFloatParam("backgroundMultiplier", 1 - f);

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

cv::Mat ImageNode::process(LoopyFunctionInput inputs)
{
    if (currentFilename == cachedFilename &&
        (inputs.count("backgroundWidth") == 0 || getFloatParam("backgroundWidth") == cachedW) &&
        (inputs.count("backgroundHeight") == 0 || getFloatParam("backgroundHeight") == cachedH)) {
        return output;
    }
    cachedFilename = currentFilename;
    cv::Mat loadedImage = cv::imread(currentFilename, CV_LOAD_IMAGE_UNCHANGED);

    int bgw = loadedImage.cols;
    int bgh = loadedImage.rows;
    int top, bottom, left, right;
    top = 0;
    bottom = 0;
    left = 0;
    right = 0;
    std::cout << bgw << " " << bgh << std::endl;
    if (inputs.count("backgroundWidth") > 0) {
        int w = getIntParam("backgroundWidth");
        cachedW = w;
        int border = w-bgw;
        left = border / 2;
        right = left + (border % 2);

    }

    if (inputs.count("backgroundHeight") > 0) {
        int h = getIntParam("backgroundHeight");
        cachedH = h;
        int border = h-bgh;
        top = border / 2;
        bottom = top + (border % 2);
    }
    cv::copyMakeBorder(loadedImage,loadedImage,top,bottom,left,right,cv::BORDER_CONSTANT,cv::Scalar(0));
    output = loadedImage;
    return output;
}

cv::Mat TickerNode::process(LoopyFunctionInput inputs)
{
    float amount = getFloatParam("amount", 1);
    output.at<float>(0, 0) = output.at<float>(0, 0) + amount;
    return output;
}

cv::Mat SineNode::process(LoopyFunctionInput inputs)
{
    float amplitude = getFloatParam("amplitude", 1);
    float period = getFloatParam("period", 1);
    float offset = getFloatParam("offset", 0);
    float time = getFloatParam("time");
    output.at<float>(0, 0) = amplitude * sin(time * period) + offset;
    return output;
}
