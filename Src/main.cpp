#include <cstdio>
#include <vector>
#include <opencv2/opencv.hpp>
#include "run_statistic.h"

using namespace std;
using namespace cv;

int main()
{
  string input_image1_path = "../Source/Image/input_image1.jpg";
  string input_image2_path = "../Source/Image/input_image2.jpg";
  string output_image_path = "../Result/Image/output_image.jpg";
  cv::Mat input_image1 = cv::imread(input_image1_path); //3 channel
  cv::Mat input_image2_b = cv::imread(input_image2_path, IMREAD_GRAYSCALE); //3 channel but only 1 channel has message
  cv::Mat output_image;

  time_statistic.start_time = Get_Time_us();
  /* split image1 to C3, add/bitwise_and image2_b/image2_b_mask */
  cv::Mat input_image2_b_mask;
  cv::threshold(input_image2_b, input_image2_b_mask, 250, 255, THRESH_BINARY_INV);
  std::vector<cv::Mat> image1_channels;
  cv::split(input_image1, image1_channels);
  cv::add(input_image2_b, image1_channels.at(0), image1_channels.at(0));
  cv::bitwise_and(input_image2_b_mask, image1_channels.at(1), image1_channels.at(1));
  cv::bitwise_and(input_image2_b_mask, image1_channels.at(2), image1_channels.at(2));
  cv::merge(image1_channels, output_image);

  time_statistic.end_time = Get_Time_us();
  printf("cost %.3lf ms", (double)(time_statistic.end_time - time_statistic.start_time) / 1000.0);

  cv::imwrite(output_image_path, output_image);

  return 0;
}

// method2
// /* convert image2_b(1channel) to image2(3channels) */
// cv::Mat input_image2;
// cv::Mat input_image2_g = Mat::zeros(input_image2_b.rows, input_image2_b.cols, CV_8UC1);
// cv::Mat input_image2_r = Mat::zeros(input_image2_b.rows, input_image2_b.cols, CV_8UC1);
// std::vector<cv::Mat> input_image2_bgr;
// input_image2_bgr.insert(input_image2_bgr.begin(), input_image2_b);
// input_image2_bgr.insert(input_image2_bgr.end(), input_image2_g);
// input_image2_bgr.insert(input_image2_bgr.end(), input_image2_r);
// cv::merge(input_image2_bgr,input_image2);
//
// /* use mask and bitwise_and to make output_image */
// cv::Mat input_image2_mask;
// cv::threshold(input_image2, input_image2_mask, 250, 255, THRESH_BINARY_INV);
// cv::bitwise_and(input_image2_mask, input_image1, output_image);