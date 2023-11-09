#include "common.hpp"
#include <set>

using namespace std;

std::map<int, std::string> common::map_label;
std::map<std::string, int> common::map_index;

/*
* Ler um arquivo de dados CSV e transforma
* na estrutura read_output
* mat_data: matriz dos dados
* mat_label: rótulos
* map_index: encontra o indice do rótulo a partir do nome
* map_label: encontra o nome do rótulo a partir do índice
*/
common::read_output common::read (std::string file_name) {
    rapidcsv::Document doc(file_name, rapidcsv::LabelParams(-1, -1));
    size_t row_count = doc.GetRowCount();
    size_t col_count = doc.GetColumnCount();

    cv::Mat mat_data = cv::Mat_<float>(row_count, col_count - 1);
    cv::Mat mat_label = cv::Mat_<int>(row_count, 1);
    std::map<int, std::vector<int>> map_label_index;

    std::vector<std::string> vec_labels = doc.GetColumn<std::string>(col_count -1);

    for (const auto& item : vec_labels) {
        if (!map_index.contains(item)) {
            int count = map_index.size();
            std::cout << item << "--" << count << std::endl;
            map_index[item] = count;
            map_label[count] = item;
        }
    }

    for (size_t i = 0; i < row_count; ++i) {
        int label = -1;
        for (size_t j = 0; j < col_count; ++j) {
            if (j == col_count - 1) {
                std::string value = doc.GetCell<std::string>(j, i);
                mat_label.at<int>(i) = map_index[value];
                label = map_index[value];
                continue;
            }

            double value = doc.GetCell<double>(j, i);
            mat_data.at<float>(i, j) = value;
        }

        map_label_index[label].push_back(i);
    }

    read_output output(mat_data, mat_label, map_label_index);
    return output;
}

std::string common::row_key (cv::Mat &mat, int row) {
    cv::Mat mat_row = mat.row(row);
    int cols = mat_row.cols;

    std::stringstream ss;
    for (int i = 0; i < cols; i++) {
        ss << mat_row.at<float>(i, 0);
        if (i < cols - 1) {
            ss << ",";
        }
    }

    return ss.str();
}

int common::random_index (std::vector<int> vec) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> disttribution(0, vec.size() - 1);
    size_t index = disttribution(generator);
    return vec[index];
}

void common::swap_rows (cv::Mat &mat_a, int row_a, cv::Mat &mat_b, int row_b) {
    for (int i = 0; i < mat_a.cols; i++) {
        float a = mat_a.at<float>(row_a, i);
        float b = mat_b.at<float>(row_b, i);
        mat_b.at<float>(row_b, i) = a;
        mat_a.at<float>(row_a, i) = b;
    }
}
