#ifndef LSH_INCLUDED
#define LSH_INCLUDED

class LSH {
public:
    LSH();
    virtual ~LSH() {};
    
    void computeParameters(int numPoints, int nQueries, int pointsDimension,
    	RealT successProbability, RealT thresholdR, PPointT *dataSetPoints,
    	PPointT* sampleQueries, Int32T nSampleQueries,
    	MemVarT availableTotalMemory, const char* flags);
    
    
};

#endif
