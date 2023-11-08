#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <rapidcsv.h>
#include <vector>
#include <map>
#include "common.hpp"
#include "knn.hpp"

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Use: ./split z1.csv z2.csv z3.csv" << std::endl;
        return 1;
    }

    string z1_name = argv[1];
    string z2_name = argv[2];
    string z3_name = argv[3];

    common::read_output output_z1 = common::read(z1_name);
    common::read_output output_z2 = common::read(z2_name);

    cout << output_z1.data << endl << output_z1.label << endl;

    for (int k = 3; k <= 13; k += 2) {
        knn::output output = knn::execute(k, output_z1.data, output_z1.label, output_z2.data, output_z2.label);
        cout << output.successes << " " << output.mistakes << endl;
    }

    // cout << output.label << endl << output.map_index.size() << endl;
    // Ptr<KNearest> knn = KNearest::create();
    // knn->setAlgorithmType(KNearest::BRUTE_FORCE);
    // knn->setDefaultK(3);
    // knn->train(output.data, ROW_SAMPLE, output.label);
    // cv::Mat test = (cv::Mat_<float>(1,4) << 1,2,3,4);
    // int result = knn->predict(test);
    // cout << "Classe prevista para o novo dado " << output.map_label[result] << endl;

    // Crie um objeto RapidCSV usando o arquivo
    // rapidcsv::Document doc("z1.csv", rapidcsv::LabelParams(-1, -1));

    // // Determine o número de linhas e colunas no arquivo CSV
    // size_t row_count = doc.GetRowCount();
    // size_t col_count = doc.GetColumnCount();

    // cv::Mat mat_data = cv::Mat_<float>(row_count, col_count - 1);
    // cv::Mat mat_label = cv::Mat_<int>(row_count, 1);
    // map<string, int> map_index;
    // map<int, string> map_label; 

    // const auto vec_labels = doc.GetColumn<string>(col_count -1);

    // int count = 0;
    // for (const auto& item : vec_labels) {
    //     if (!map_index.contains(item)) {
    //         map_index[item] = count;
    //         map_label[count] = item;
    //         count++;
    //     }
    // }

    // for (size_t i = 0; i < row_count; ++i) {
    //     for (size_t j = 0; j < col_count; ++j) {
    //         if (j == col_count - 1) {
    //             string value = doc.GetCell<string>(j, i);
    //             mat_label.at<int>(i) = map_index[value];
    //             continue;
    //         }

    //         double value = doc.GetCell<double>(j, i);
    //         mat_data.at<float>(i, j) = value;
    //     }
    // }

    // Ptr<KNearest> knn = KNearest::create();
    // knn->setAlgorithmType(KNearest::BRUTE_FORCE);
    // knn->setDefaultK(15); // Definindo o valor de K para o algoritmo
    // knn->train(mat_data, ROW_SAMPLE, mat_label);
    // cv::Mat test = (cv::Mat_<float>(1,4) << 1,2,3,4);
    // int result = knn->predict(test);
    // cout << "Classe prevista para o novo dado " << map_label[result] << endl;



    // // Crie uma matriz do OpenCV para armazenar os dados do CSV
    // cv::Mat csvMat(rowCount, colCount, CV_32S);

    // // Preencha a matriz com os dados do CSV
    // for (size_t row = 0; row < rowCount; ++row) {
    //     for (size_t col = 0; col < colCount; ++col) {
    //         csvMat.at<int>(row, col) = doc.GetCell<int>(row, col);
    //     }
    // }

    // // Exibir a matriz OpenCV para verificar se os dados foram lidos corretamente
    // std::cout << "Matriz OpenCV:" << std::endl;
    // std::cout << csvMat << std::endl;

    // return 0;
    // // Seus dados de treinamento
    // Mat trainData = (Mat_<float>(6, 2) << 2, 3, 3, 4, 3, 5, 4, 2, 5, 3, 6, 4); // Exemplo de dados de entrada
    // Mat labels = (Mat_<int>(6, 1) << 0, 0, 0, 1, 1, 1); // Exemplo de rótulos de classes correspondentes

    // // Inicializando o modelo KNN
    // Ptr<KNearest> knn = KNearest::create();
    // knn->setAlgorithmType(KNearest::BRUTE_FORCE);
    // knn->setDefaultK(1); // Definindo o valor de K para o algoritmo

    // // Treinamento do modelo
    // knn->train(trainData, ROW_SAMPLE, labels);

    // // Dados de teste
    // Mat testData = (Mat_<float>(1, 2) << 2, 3); // Exemplo de um novo dado a ser classificado

    // // Fazendo a previsão com o modelo treinado
    // Mat results, neighborResponses, dists;
    // // knn->findNearest(testData, knn->getDefaultK(), results, neighborResponses, dists);
    // int result = knn->predict(testData);

    // cout << "Classe prevista para o novo dado " << result << endl;

    // return 0;
}
