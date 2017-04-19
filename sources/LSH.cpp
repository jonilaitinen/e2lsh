// This file implements the functionality previously found in LSHMain

#include "LSH.h"
#include "headers.h"

LSH::LSH() {

}

void LSH::computeParametersForData(const std::vector<std::vector<double> >& data) {

	if(data.empty()) {
		printf("Empty data vector!");
		return;
	}

	IntT nPoints = data.size();
	IntT pointsDimension = data[0].size();
	RealT successProbability = 0.9;
	RealT thresholdR = 0.3; // 0.005 0.01 0.05 0.1 0.15 0.2 0.25 0.3 0.31 0.32 0.33 0.34 0.35 0.36 0.38 0.4
	MemVarT availableTotalMemory = 4000000; // ~4GB

	PPointT* dataSet = NULL;
	FAILIF(NULL == (dataSet = (PPointT*)MALLOC(nPoints * sizeof(PPointT))));

	for(IntT i = 0; i < data.size(); i++) {
		PPointT p;
		RealT sqrLength = 0;
		FAILIF(NULL == (p = (PPointT)MALLOC(sizeof(PointT))));
		FAILIF(NULL == (p->coordinates = (RealT*)MALLOC(pointsDimension * sizeof(RealT))));

		for(IntT d = 0; d < pointsDimension; d++){
			p->coordinates[d] = data[i][d];
			sqrLength += SQR(p->coordinates[d]);
		}
		p->index = i;
		p->sqrLength = sqrLength;
		dataSet[i] = p;
	}

	computeParameters(nPoints, pointsDimension, successProbability, thresholdR, dataSet, availableTotalMemory);

}

void LSH::computeParameters(IntT nPoints, IntT pointsDimension,
		RealT successProbability, RealT thresholdR, PPointT *dataSetPoints,
		MemVarT availableTotalMemory) {
	printf("Start compute parameters...\n");

	IntT nRadii = 1;
	RealT *listOfRadii = NULL;
	RealT *memRatiosForNNStructs = NULL;
	FAILIF(NULL == (listOfRadii = (RealT*)MALLOC(nRadii * sizeof(RealT))));
	FAILIF(NULL == (memRatiosForNNStructs = (RealT*)MALLOC(nRadii * sizeof(RealT))));
	listOfRadii[0] = thresholdR;
	memRatiosForNNStructs[0] = 1;

	if (nPoints > MAX_N_POINTS) {
		printf("Error: the structure supports at most %d points (%d were specified).\n",
				MAX_N_POINTS, nPoints);
		fprintf(ERROR_OUTPUT,
				"Error: the structure supports at most %d points (%d were specified).\n",
				MAX_N_POINTS, nPoints);
		return;
	}

	// generate sample queries
	IntT nSampleQueries = 100;
	PPointT sampleQueries[nSampleQueries];
	Int32T sampleQBoundaryIndeces[nSampleQueries];

	// In this cases, we need to generate a sample query set for
	// computing the optimal parameters.

	// Generate a sample query set.
	// Choose several data set points for the sample query points.
	printf("Generate sample queries...\n");
	for (IntT i = 0; i < nSampleQueries; i++) {
		sampleQueries[i] = dataSetPoints[genRandomInt(0, nPoints - 1)];
	}

	// Compute the array sampleQBoundaryIndeces that specifies how to
	// segregate the sample query points according to their distance
	// to NN.
	sortQueryPointsByRadii(pointsDimension, nSampleQueries, sampleQueries,
			nPoints, dataSetPoints, nRadii, listOfRadii,
			sampleQBoundaryIndeces);
	// sample queries generated

	// Only compute the R-NN DS parameters and output them to stdout.
	printf("radii count: %d\n", nRadii);
	transformMemRatios(nRadii, memRatiosForNNStructs);
	for (IntT i = 0; i < nRadii; i++) {
		// which sample queries to use
		Int32T segregatedQStart = (i == 0) ? 0 : sampleQBoundaryIndeces[i - 1];
		Int32T segregatedQNumber = nSampleQueries - segregatedQStart;
		if (segregatedQNumber == 0) {
			// XXX: not the right answer
			segregatedQNumber = nSampleQueries;
			segregatedQStart = 0;
		}
		ASSERT(segregatedQStart < nSampleQueries);
		ASSERT(segregatedQStart >= 0);
		ASSERT(segregatedQStart + segregatedQNumber <= nSampleQueries);
		ASSERT(segregatedQNumber >= 0);
		RNNParametersT optParameters = computeOptimalParameters(listOfRadii[i],
				successProbability, nPoints, pointsDimension, dataSetPoints,
				segregatedQNumber, sampleQueries + segregatedQStart,
				(MemVarT) ((availableTotalMemory - totalAllocatedMemory)
						* memRatiosForNNStructs[i]));
		printRNNParameters(stdout, optParameters);
	}

}

// Tranforming <memRatiosForNNStructs> from
// <memRatiosForNNStructs[i]=ratio of mem/total mem> to
// <memRatiosForNNStructs[i]=ratio of mem/mem left for structs i,i+1,...>.
void LSH::transformMemRatios(IntT nRadii, RealT* memRatiosForNNStructs) {
	RealT sum = 0;
	for (IntT i = nRadii - 1; i >= 0; i--) {
		sum += memRatiosForNNStructs[i];
		memRatiosForNNStructs[i] = memRatiosForNNStructs[i] / sum;
		//DPRINTF("%0.6lf\n", memRatiosForNNStructs[i]);
	}
	ASSERT(sum <= 1.000001);
}

