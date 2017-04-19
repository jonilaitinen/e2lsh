#ifndef LSH_INCLUDED
#define LSH_INCLUDED

#include <stdio.h>
#include <vector>

#include "BasicDefinitions.h"
#include "Geometry.h"

class LSH {
public:
    LSH();
    virtual ~LSH() {};
    
    void computeParametersForData(const std::vector<std::vector<double> >& data);

    void computeParameters(IntT numPoints, int pointsDimension,
    	RealT successProbability, RealT thresholdR, PPointT *dataSetPoints,
    	MemVarT availableTotalMemory);

private:
    void transformMemRatios(IntT nRadii, RealT* memRatiosForNNStructs);
    
};

#endif
