#ifndef COMMON
#define COMMON

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <rapidcsv.h>
#include <map>

namespace common {
  struct read_output {
    cv::Mat data;
    cv::Mat label;
    std::map<std::string, int> map_index;
    std::map<int, std::string> map_label;
    read_output(cv::Mat& d, cv::Mat& l, std::map<std::string, int>& mi, std::map<int, std::string>& ml)
      : data(d), label(l), map_index(mi), map_label(ml) {}
  };

  read_output read(std::string file_name);
}

#endif