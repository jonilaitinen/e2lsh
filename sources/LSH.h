#ifndef LSH_INCLUDED
#define LSH_INCLUDED

#include <stdio.h>
#include <vector>

#include "BasicDefinitions.h"
#include "Geometry.h"
#include "RNNParametersT.h"

class LSH {
public:
    LSH();
    virtual ~LSH() {};
    
    std::vector<RNNParametersT> computeParametersForData(
    		const std::vector<std::vector<double> >& data,
			RealT thresholdR, RealT successProbability = 0.9,
			MemVarT availableTotalMemoryKB = 4000000); // 4GB

private:
    std::vector<RNNParametersT> computeParameters(IntT numPoints,
    		int pointsDimension, RealT successProbability,
			RealT thresholdR, PPointT *dataSetPoints,
        	MemVarT availableTotalMemory);

    void transformMemRatios(IntT nRadii, RealT* memRatiosForNNStructs);
    
};

#endif
