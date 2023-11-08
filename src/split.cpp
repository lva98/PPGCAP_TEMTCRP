#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "rapidcsv.h"
#include <map>

// Função para dividir os dados mantendo a proporção dos rótulos
// void splitData(const std::string &inputFile, double p1, double p2, double p3) {
//     rapidcsv::Document doc(inputFile, rapidcsv::LabelParams(-1, -1));

//     std::vector<std::vector<std::string>> data;
//     std::vector<std::vector<std::string>> dataRemaining;

//     // Lê os dados do arquivo CSV
//     for (int i = 0; i < doc.GetRowCount(); ++i) {
//         std::vector<std::string> row;
//         for (int j = 0; j < doc.GetColumnCount(); ++j) {
//             row.push_back(doc.GetCell<std::string>(j, i));
//         }
//         data.push_back(row);
//     }

//     // Ordena os dados com base nos rótulos (última coluna)
//     std::sort(data.begin(), data.end(), [](const std::vector<std::string> &a, const std::vector<std::string> &b) {
//         return a.back() < b.back();
//     });

//     // Separa os dados mantendo a proporção dos rótulos
//     int pos1 = data.size() * p1;
//     int pos2 = data.size() * (p1 + p2);

//     std::vector<std::vector<std::string>> firstSet(data.begin(), data.begin() + pos1);
//     std::vector<std::vector<std::string>> secondSet(data.begin() + pos1, data.begin() + pos2);
//     std::vector<std::vector<std::string>> thirdSet(data.begin() + pos2, data.end());

//     // Escreve os dados nos arquivos de saída
//     rapidcsv::Document output1(inputFile + "_set1.csv", rapidcsv::LabelParams(-1, -1));
//     rapidcsv::Document output2(inputFile + "_set2.csv", rapidcsv::LabelParams(-1, -1));
//     rapidcsv::Document output3(inputFile + "_set3.csv", rapidcsv::LabelParams(-1, -1));

//     for (const auto &row : firstSet) {
//       output1.AddRow(row);
//     }

//     for (const auto &row : secondSet) {
//         output2.AddRow(row);
//     }

//     for (const auto &row : thirdSet) {
//         output3.AddRow(row);
//     }
// }
using namespace std;

void save_to_file (vector<vector<string>> &vec, string name) {
  rapidcsv::Document doc;
  for (size_t i = 0; i < vec.size(); ++i) {
    for (size_t j = 0; j < vec[i].size(); ++j) {
      doc.SetCell(j, i - 1, vec[i][j]);
    }
  }

  doc.Save(name);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "Use: ./split data.csv p1 p2 p3" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    double ratios[3] = {std::stod(argv[2]) / 100.0, std::stod(argv[3]) / 100.0, std::stod(argv[4]) / 100.0};

    rapidcsv::Document doc(inputFile, rapidcsv::LabelParams(-1, -1));

    map<string, vector<vector<string>>> data;
    map<string, int> map_count;

    for (int i = 0; i < doc.GetRowCount(); ++i) {
      std::vector<std::string> row;
      string label;

      for (int j = 0; j < doc.GetColumnCount(); ++j) {
        auto cell_value = doc.GetCell<std::string>(j, i);
        if (j == doc.GetColumnCount() - 1) {
          label = cell_value;
        }
        row.push_back(cell_value);
      }

      map_count[label]++;

      if (!data.contains(label)) {
        data[label] = vector<vector<string>>();
      }

      data[label].push_back(row);
    }

    for (int i = 0; i < 2; i++) {
      double ratio = ratios[i];
      vector<vector<string>> output;

      for (auto &pair : data) {
        vector<vector<string>> &vec = pair.second;
        const string key = pair.first;
        const int count = floor(map_count[key] * ratio);

        move(vec.begin(), vec.begin() + count, back_inserter(output));
        vec.erase(vec.begin(), vec.begin() + count);
      }

      stringstream stream;
      stream << "z" << i+1 << ".csv";
      save_to_file(output, stream.str());
    }

    vector<vector<string>> output;
    for (const auto &pair : data) {
      auto vec = pair.second;
      output.insert(output.begin(), vec.begin(), vec.end());
    }

    save_to_file(output, "z3.csv");

    cout << "Ok!" << endl;
    return 0;
}
