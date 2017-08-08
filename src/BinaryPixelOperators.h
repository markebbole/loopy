#ifndef BINARY_PIXEL_OPERATORS
#define BINARY_PIXEL_OPERATORS
#include <opencv2/opencv.hpp>

struct BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second);
};

struct AddPixelOperator : public BinaryPixelOperator
{
    float foregroundMultiplier;
    float backgroundMultiplier;
    AddPixelOperator(float foregroundMultiplier, float backgroundMultiplier) : BinaryPixelOperator() {
        this->foregroundMultiplier = foregroundMultiplier;
        this->backgroundMultiplier = backgroundMultiplier;
    }
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second);
};

struct MultiplyPixelOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second);
};

struct AddPixelModOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second);
};

struct SubtractPixelOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second);
};

struct DividePixelOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second);
};

#endif
