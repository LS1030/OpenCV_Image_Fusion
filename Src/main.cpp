#include <cstdio>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
  string input_image1_path = "../Source/Image/input_image1.jpg";
  string input_image2_path = "../Source/Image/input_image2.jpg";
  string output_image_path = "../Result/Image/output_image.jpg";

  cv::Mat input_image1 = cv::imread(input_image1_path); //3 channel
  cv::Mat input_image2 = cv::imread(input_image2_path, IMREAD_GRAYSCALE); //3 channel but only 1 channel has message
  cv::Mat input_image2_mask;
  cv::threshold(input_image2, input_image2_mask, 250, 255, THRESH_BINARY_INV);
  cv::Mat output_image;

  std::vector<cv::Mat> image1_channels;
  cv::split(input_image1, image1_channels);
  cv::Mat image1_channel_b = image1_channels.at(0);
  cv::Mat image1_channel_g = image1_channels.at(1);
  cv::Mat image1_channel_r = image1_channels.at(2);
  cv::add(input_image2, image1_channels.at(0), image1_channels.at(0));
  cv::bitwise_and(input_image2_mask, image1_channels.at(1), image1_channels.at(1));
  cv::bitwise_and(input_image2_mask, image1_channels.at(2), image1_channels.at(2));
  cv::merge(image1_channels, output_image);

  cv::imwrite(output_image_path, output_image);

  return 0;
}
