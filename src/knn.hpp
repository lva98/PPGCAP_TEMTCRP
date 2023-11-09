#ifndef KNN
#define KNN

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <map>
#include <vector>

namespace knn {
  struct input {
    cv::Mat train_data;
    cv::Mat train_label;
    cv::Mat test_data;
    cv::Mat test_label; 
    input (cv::Mat& trd, cv::Mat& trl, cv::Mat& ted, cv::Mat& tel)
      : train_data(trd), train_label(trl), test_data(ted), test_label(tel) {}
  };

  struct output {
    std::vector<bool> result;
    std::map<int, int> mistakes_by_labels;
    std::map<int, int> successes_by_labels;
    std::map<int, std::vector<int>> successes_data;
    std::map<int, std::vector<int>> mistakes_data;
    int mistakes;
    int successes;

    output (std::vector<bool>& r, std::map<int, int>& mbl, std::map<int, int>& sbl, std::map<int, std::vector<int>> sd, std::map<int, std::vector<int>> md, int m, int s)
      : result(r), mistakes_by_labels(mbl), successes_by_labels(sbl), mistakes_data(md), successes_data(sd), mistakes(m), successes(s) {}
  };

  output execute (int k, cv::Mat& train_data, cv::Mat& train_label, cv::Mat& test_data, cv::Mat& test_label);
}

#endif
