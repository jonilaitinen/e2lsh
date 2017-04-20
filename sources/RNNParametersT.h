#ifndef RNNPARAMETERST_INCLUDED
#define RNNPARAMETERST_INCLUDED

typedef struct _RNNParametersT {
  RealT parameterR; // parameter R of the algorithm.
  RealT successProbability; // the success probability 1-\delta
  IntT dimension; // dimension of points.
  RealT parameterR2; // = parameterR^2

  // Whether to use <u> hash functions instead of usual <g>
  // functions. When this flag is set to TRUE, <u> functions are
  // generated (which are roughly k/2-tuples of LSH), and a <g>
  // function is a pair of 2 different <u> functions.
  BooleanT useUfunctions;

  IntT parameterK; // parameter K of the algorithm.
  
  // parameter M (# of independent tuples of LSH functions)
  // if useUfunctions==TRUE, parameterL = parameterM * (parameterM - 1) / 2
  // if useUfunctions==FALSE, parameterL = parameterM
  IntT parameterM;

  IntT parameterL; // parameter L of the algorithm.
  RealT parameterW; // parameter W of the algorithm.
  IntT parameterT; // parameter T of the algorithm.

  // The type of the hash table used for storing the buckets (of the
  // same <g> function).
  IntT typeHT;
} RNNParametersT, *PRNNParametersT;

#endif