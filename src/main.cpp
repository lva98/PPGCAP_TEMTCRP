// This is an interactive demo, so feel free to change the code and click the 'Run' button.

// This simple program uses the mlpack::neighbor::NeighborSearch object
// to find the nearest neighbor of each point in a dataset using the L1 metric,
// and then print the index of the neighbor and the distance of it to stdout.

#include <iostream>
#include <mlpack/mlpack.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>

using namespace mlpack;

int main() {
    // Carregar arquivo CSV usando Armadillo
    arma::mat data;

    if(data.load("data/iris/iris.data")) {
        arma::Mat<size_t> labels = arma::conv_to<arma::Row<size_t>>::from(data.row(data.n_rows - 1));
        arma::mat dataset = data.submat(0, 0, data.n_rows - 2, data.n_cols - 1);
        NeighborSearch<NearestNeighborSort, metric::EuclideanDistance> nnSearch(dataset);

        nnSearch.Train(dataset);

        // Test data for classification.
        arma::mat testSet; // Insert your test data here for classification.
        testSet.load("data/iris/test.csv");

        // Set the number of neighbors for classification.
        const size_t k = 3;  // Set the value of k (number of nearest neighbors).

        // Find the nearest neighbors.
        arma::Mat<size_t> neighbors;
        arma::mat distances;
        nnSearch.Search(testSet, k, neighbors, distances);

        // Print the indices of the nearest neighbors.
        std::cout << "Indices of nearest neighbors:" << std::endl;
        std::cout << neighbors << std::endl;

        // Print the distances to the nearest neighbors.
        std::cout << "Distances to nearest neighbors:" << std::endl;
        std::cout << distances << std::endl;
    } else {
        // Falha ao carregar o arquivo
        std::cout << "Falha ao carregar o arquivo." << std::endl;
    }

    return 0;
}