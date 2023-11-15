#include "knn.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <vector>

using namespace cv;
using namespace cv::ml;

knn::output knn::execute (int k, cv::Mat& train_data, cv::Mat& train_label, cv::Mat& test_data, cv::Mat& test_label) {
  std::vector<bool> result;
  std::map<int, int> mistakes_by_labels;
  std::map<int, int> success_by_labels;
  std::map<int, std::vector<int>> successes_data;
  std::map<int, std::vector<int>> mistakes_data;
  std::vector<int> attempts;
  int mistakes = 0;
  int successes = 0;

  Ptr<KNearest> knn = KNearest::create();
  knn->setAlgorithmType(KNearest::BRUTE_FORCE);
  knn->setDefaultK(k);
  knn->train(train_data, ROW_SAMPLE, train_label);
  cv::Mat predicts;
  knn->predict(test_data, predicts);

  for (int i = 0; i < predicts.rows; ++i) {
    const int attempt = (int) predicts.at<float>(i, 0);
    const int answer = test_label.at<int>(i, 0);
    attempts.push_back(attempt);

    bool is_correct = attempt == answer;
    if (is_correct) {
      ++successes;
      successes_data[answer].push_back(i);
      result.push_back(true);
      success_by_labels[attempt]++;
    } else {
      ++mistakes;
      mistakes_data[answer].push_back(i);
      result.push_back(false);
      mistakes_by_labels[attempt]++;
    }
  }
  
  return knn::output(result, attempts, mistakes_by_labels, success_by_labels, successes_data, mistakes_data, mistakes, successes);
}