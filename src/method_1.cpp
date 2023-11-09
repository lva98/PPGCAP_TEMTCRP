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
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    if (argc != 4 && argc != 5) {
        std::cout << "Use: ./split z1.csv z2.csv z3.csv" << std::endl;
        return 1;
    }

    int label_column = -1;
    if (argc == 5) {
        label_column = std::stoi(argv[4]);
    }

    string z1_name = argv[1];
    string z2_name = argv[2];
    string z3_name = argv[3];
    vector<double> successes_ratio;

    common::read_output output_z1 = common::read(z1_name, label_column);
    common::read_output output_z2 = common::read(z2_name, label_column);
    common::read_output output_z3 = common::read(z3_name, label_column);

    int best_k, successes = 0;
    printf("finding_best_k\n");
    printf("i,k,successes,mistakes\n");
    for (int k = 3, i = 0; k <= 13; k += 1, ++i) {
        knn::output output = knn::execute(k, output_z1.data, output_z1.label, output_z2.data, output_z2.label);
        if (output.successes > successes) {
            successes = output.successes;
            best_k = k;
        }
        printf("%d,%d,%d,%d\n", i, k, output.successes, output.mistakes);
        if (output.mistakes == 0) {
            break;
        }
    }
    printf("best k = %d\n\n", best_k);

    int total = 30;
    while (total--) {
        printf("iteration_%d\n", 30 - total);
        printf("-\n");
        printf("finding_best_t\n");
        printf("t,successes,mistakes\n");

        cv::Mat best_z1;
        cv::Mat best_z1_labels;
        successes = 0;
        int t_count = 25;
        int t_best = -1;

        for (int t = 0; t < t_count; t++) {
            knn::output output = knn::execute(best_k, output_z1.data, output_z1.label, output_z2.data, output_z2.label);
            printf("%d,%d,%d\n", t, output.successes, output.mistakes);

            if (output.successes > successes) {
                best_z1 = output_z1.data.clone();
                best_z1_labels = output_z1.label.clone();
                successes = output.successes;
                t_best = t;
            }

            if (output.mistakes == 0) {
                break;
            }

            for (const auto &pair: output.mistakes_data) {
                int label = pair.first;

                std::vector<int> &indexes_z1 = output_z1.map_label_index[label];
                std::vector<int> indexes_z2 = pair.second;

                for (const auto index_z2: indexes_z2) {
                    int random_index_z1 = common::random_index(indexes_z1);
                    common::swap_rows(output_z1.data, random_index_z1, output_z2.data, index_z2);
                }
            }
        }
        printf("best t = %d\n", t_best);
        printf("-\n");

        knn::output output = knn::execute(best_k, best_z1, best_z1_labels, output_z3.data, output_z3.label);
        double success_ratio = output.successes * 100 / (double) output.result.size();
        successes_ratio.push_back(success_ratio);

        printf("result\n");
        printf("successes,mistakes,success_ratio\n");
        printf("%d,%d,%.2lf%\n\n", output.successes, output.mistakes, success_ratio);

        output_z1 = common::read(z1_name, label_column);
        output_z2 = common::read(z2_name, label_column);
        output_z3 = common::read(z3_name, label_column);
    }

    cv::Mat success_ratio_mat(successes_ratio);
    cv::Scalar mean, stddev;
    cv::meanStdDev(success_ratio_mat, mean, stddev);

    printf("summary\n");
    printf("mean,stddev\n");
    printf("%.2lf%,%.2lf%\n", mean[0], stddev[0]);
}
