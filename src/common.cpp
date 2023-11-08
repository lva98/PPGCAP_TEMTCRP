#include "common.hpp"

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

    // Determine o número de linhas e colunas no arquivo CSV
    size_t row_count = doc.GetRowCount();
    size_t col_count = doc.GetColumnCount();

    cv::Mat mat_data = cv::Mat_<float>(row_count, col_count - 1);
    cv::Mat mat_label = cv::Mat_<int>(row_count, 1);
    std::map<std::string, int> map_index;
    std::map<int, std::string> map_label; 

    const auto vec_labels = doc.GetColumn<std::string>(col_count -1);

    int count = 0;
    for (const auto& item : vec_labels) {
        if (!map_index.contains(item)) {
            map_index[item] = count;
            map_label[count] = item;
            count++;
        }
    }

    for (size_t i = 0; i < row_count; ++i) {
        for (size_t j = 0; j < col_count; ++j) {
            if (j == col_count - 1) {
                std::string value = doc.GetCell<std::string>(j, i);
                mat_label.at<int>(i) = map_index[value];
                continue;
            }

            double value = doc.GetCell<double>(j, i);
            mat_data.at<float>(i, j) = value;
        }
    }

    read_output output(mat_data, mat_label, map_index, map_label);
    return output;
}