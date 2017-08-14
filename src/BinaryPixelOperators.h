#ifndef BINARY_PIXEL_OPERATORS
#define BINARY_PIXEL_OPERATORS
#include <opencv2/opencv.hpp>

struct BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier);
};

struct AddPixelOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier);
};

struct MultiplyPixelOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier);
};

struct AddPixelModOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier);
};

struct SubtractPixelOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier);
};

struct DividePixelOperator : public BinaryPixelOperator
{
    virtual cv::Vec4b operator()(cv::Vec4b& first, cv::Vec4b& second, float foregroundMultiplier, float backgroundMultiplier);
};

#endif
