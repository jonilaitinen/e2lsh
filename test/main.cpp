

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "LSH.h"


int main(int argc, char **argv) {
    
    LSH lshComputation;
    int D = 12800;

    // make a random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100, 100);
        
    // generate some test data
    std::vector<std::vector<double> > data;
    for(int i = 0; i < 1000; i++) {
        std::vector<double> feature;
        for(int j = 0; j < D; j++) {
            feature.push_back(dis(gen));
        }
        data.push_back(feature);
    }

    std::cout << "Starting to compute parameters..." << std::endl;
    std::vector<RNNParametersT> result = lshComputation.computeParametersForData(data, 0.1);
    std::cout << "Parameters computed" << std::endl;
    
    return 0;
}
