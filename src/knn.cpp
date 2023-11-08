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
  int mistakes = 0;
  int successes = 0;

  Ptr<KNearest> knn = KNearest::create();
  knn->setAlgorithmType(KNearest::BRUTE_FORCE);
  knn->setDefaultK(k);
  knn->train(train_data, ROW_SAMPLE, train_label);
  cv::Mat predicts;
  knn->predict(test_data, predicts);

  for (int i = 0; i < predicts.rows; ++i) {
    const int attempt = predicts.at<float>(i, 0);
    const int answer = test_label.at<int>(i, 0); 

    bool is_correct = attempt == answer;
    mistakes += (!is_correct) ? 1 : 0;
    successes += (is_correct) ? 0 : 1;

    if (is_correct) {
      ++successes;
      result.push_back(true);
      success_by_labels[attempt]++;
    } else {
      ++mistakes;
      result.push_back(false);
      mistakes_by_labels[attempt]++;
    }
  }

  return knn::output(result, mistakes_by_labels, success_by_labels, mistakes, successes);
}