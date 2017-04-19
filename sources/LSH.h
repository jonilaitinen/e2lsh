#ifndef LSH_INCLUDED
#define LSH_INCLUDED

#include <stdio.h>
#include "BasicDefinitions.h"
#include "Geometry.h"

class LSH {
public:
    LSH();
    virtual ~LSH() {};
    
    void computeParameters(IntT numPoints, int pointsDimension,
    	RealT successProbability, RealT thresholdR, PPointT *dataSetPoints,
    	MemVarT availableTotalMemory);

private:
    void transformMemRatios(IntT nRadii, RealT* memRatiosForNNStructs);
    
};

#endif
