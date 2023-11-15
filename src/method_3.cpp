#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <rapidcsv.h>
#include <vector>
#include <map>
#include "common.hpp"
#include "knn.hpp"

using namespace cv;
using namespace cv::ml;
using namespace std;

int main (int argc, char *argv[]) {
    std::random_device rd;
    std::mt19937 generator(rd());
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    if (argc != 3) {
        std::cout << "Use: ./split train.csv test.csv" << std::endl;
        return 1;
    }

    string z1_name = argv[1];
    string z2_name = argv[2];

    common::read_output output_z1 = common::read(z1_name, -1);
    common::read_output output_z2 = common::read(z2_name, -1);
    map<int, vector<int>> attempts_by_k;

    int t_count = 20;
    int best_k, successes = 0;
    printf("k_classifiers\n");
    printf("i,K,Successes,Mistakes,Success_Ratio\n");
    for (int k = 1, i = 0; k <= 13; k += 2, ++i) {
        knn::output output = knn::execute(k, output_z1.data, output_z1.label, output_z2.data, output_z2.label);
        attempts_by_k[k] = output.attempts;
        double success_ratio = output.successes * 100.0 / (double) (output.successes + output.mistakes);
        printf("%d,%d,%d,%d,%.2lf%\n", i, k, output.successes, output.mistakes, success_ratio);
    }

    int method_3_successes = 0;
    int method_3_mistakes = 0;
    printf("\nmethod_3\n");
    printf("Successes,Mistakes,Success_Ratio\n");
    for (int i = 0; i < output_z2.label.rows; i++) {
        map<int, int> frequency_map;

        for (auto& item: attempts_by_k) {
            vector<int> &attempts = item.second;
            int label = attempts[i];
            frequency_map[attempts[i]]++;
        }

        int max_frequency = 0;
        for (auto& item: frequency_map) {
            int frequency = item.second;
            if (frequency > max_frequency) {
                max_frequency = frequency;
            }
        }
        
        vector<int> labels;
        for (auto& item: frequency_map) {
            int frequency = item.second;
            int label = item.first;
            if (frequency == max_frequency) {
                labels.push_back(label);
            }
        }

        std::uniform_int_distribution<size_t> disttribution(0, labels.size() - 1);
        size_t sorted_index = disttribution(generator);
        int attempt_label = labels[sorted_index];

        const int answer = output_z2.label.at<int>(i, 0);
        bool is_correct = attempt_label == answer;

        is_correct ? ++method_3_successes : ++method_3_mistakes;
    }

    double success_ratio = method_3_successes * 100.0 / (method_3_successes + method_3_mistakes);
    printf("%d,%d,%.2lf%\n", method_3_successes, method_3_mistakes, success_ratio);
}
