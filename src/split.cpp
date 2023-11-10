#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "rapidcsv.h"
#include <map>

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
    if (argc != 5 && argc != 6) {
        std::cout << "Use: ./split data.csv p1 p2 p3" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    double ratios[3] = {std::stod(argv[2]) / 100.0, std::stod(argv[3]) / 100.0, std::stod(argv[4]) / 100.0};
    int label_column = -1;
    if (argc == 6) {
      label_column = std::stoi(argv[5]);
    }

    rapidcsv::Document doc(inputFile, rapidcsv::LabelParams(-1, -1));

    map<string, vector<vector<string>>> data;
    map<string, int> map_count;

    for (int i = 0; i < doc.GetRowCount(); ++i) {
      std::vector<std::string> row;
      string label;

      for (int j = 0; j < doc.GetColumnCount(); ++j) {
        auto cell_value = doc.GetCell<std::string>(j, i);
        if ((label_column == -1 && j == doc.GetColumnCount() - 1) || j == label_column) {
          label = cell_value;
        } else {
          row.push_back(cell_value);
        }
      }

      row.push_back(label);

      map_count[label]++;
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
