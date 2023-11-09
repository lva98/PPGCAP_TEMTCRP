#ifndef COMMON
#define COMMON

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <rapidcsv.h>
#include <map>
#include <random>

namespace common {
  extern std::map<int, std::string> map_label;
  extern std::map<std::string, int> map_index;

  struct read_output {
    cv::Mat data;
    cv::Mat label;
    std::map<int, std::vector<int>> map_label_index;
    read_output(cv::Mat& d, cv::Mat& l, std::map<int, std::vector<int>> mli)
      : data(d), label(l), map_label_index(mli) {}
  };

  void swap_rows (cv::Mat &mat_a, int row_a, cv::Mat &mat_b, int row_b);
  int random_index (std::vector<int> vec);
  read_output read (std::string file_name);
  std::string row_key (cv::Mat &mat, int row);  
}

#endif