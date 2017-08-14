#include "BinaryPixelOperators.h"

cv::Vec4b BinaryPixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier)
{
    return cv::Vec4b();
}

cv::Vec4b AddPixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier)
{
    if (first[3] == 0) {
        return second;
    } else {
        float a = foregroundMultiplier * first[0] + backgroundMultiplier * second[0];
        float b = foregroundMultiplier * first[1] + backgroundMultiplier * second[1];
        float c = foregroundMultiplier * first[2] + backgroundMultiplier * second[2];
        
        return cv::Vec4b(MIN(floor(a), 255),
                         MIN(floor(b), 255),
                         MIN(floor(c), 255),
                         MAX(first[3], second[3]));

    }
}

cv::Vec4b SubtractPixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier)
{
    if (first[3] == 0) {
        return second;
    } else {
        float a = foregroundMultiplier * first[0] - backgroundMultiplier * second[0];
        float b = foregroundMultiplier * first[1] - backgroundMultiplier * second[1];
        float c = foregroundMultiplier * first[2] - backgroundMultiplier * second[2];

        return cv::Vec4b(std::abs((int)a),
                         std::abs((int)b),
                         std::abs((int)c),
                         MAX(first[3], second[3]));
    }
}

cv::Vec4b AddPixelModOperator::operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier)
{
    if (first[3] == 0) {
        return second;
    } else {
        float a = foregroundMultiplier * first[0] + backgroundMultiplier * second[0];
        float b = foregroundMultiplier * first[1] + backgroundMultiplier * second[1];
        float c = foregroundMultiplier * first[2] + backgroundMultiplier * second[2];
        return cv::Vec4b((int)floor(a) % 256,
                         (int)floor(b) % 256,
                         (int)floor(c) % 256,
                         MAX(first[3], second[3]));
    }
}

cv::Vec4b MultiplyPixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier)
{
    if (first[3] == 0) {
        return second;
    } else {
        float a = foregroundMultiplier * first[0] * backgroundMultiplier * second[0];
        float b = foregroundMultiplier * first[1] * backgroundMultiplier * second[1];
        float c = foregroundMultiplier * first[2] * backgroundMultiplier * second[2];
        return cv::Vec4b((int)floor(a / 255.0),
                         (int)floor(b / 255.0),
                         (int)floor(c / 255.0),
                         MAX(first[3], second[3]));
    }
}

cv::Vec4b DividePixelOperator::operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier)
{
    if (first[3] == 0) {
        return second;
    } else {
        float a = foregroundMultiplier * first[0] / backgroundMultiplier * second[0];
        float b = foregroundMultiplier * first[1] / backgroundMultiplier * second[1];
        float c = foregroundMultiplier * first[2] / backgroundMultiplier * second[2];
        return cv::Vec4b(MIN(floor(255.0 * a), 255),
                         MIN(floor(255.0 * b), 255),
                         MIN(floor(255.0 * c), 255),
                         MAX(first[3], second[3]));
    }
}
