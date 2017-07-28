#include "BinaryPixelOperators.h"

cv::Vec4b BinaryPixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second)
{
    return cv::Vec4b();
}

cv::Vec4b AddPixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second)
{
    if (first[3] == 0) {
        return second;
    } else {
        return foregroundMultiplier * first + (1-foregroundMultiplier) * second;
    }
}

cv::Vec4b AddPixelModOperator::operator()(cv::Vec4b& first, cv::Vec4b& second)
{
    if (first[3] == 0) {
        return second;
    } else {
        return cv::Vec4b((first[0]+second[0])%256, (first[1]+second[1])%256, (first[2]+second[2])%256, MAX(first[3], second[3]));
    }
}

cv::Vec4b MultiplyPixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second)
{
    if (first[3] == 0) {
        return second;
    } else {
        return cv::Vec4b(first[0]*second[0], first[1]*second[1], first[2]*second[2], MAX(first[3], second[3]));
    }
}