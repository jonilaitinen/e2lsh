#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libe2lshGen.la

#######################################
# Build information for each library

# Sources for libe2lshGen
libe2lshGen_la_SOURCES = \
	../sources/BucketHashing.cpp \
	../sources/compareOutputs.cpp \
	../sources/Geometry.cpp \
	../sources/GlobalVars.cpp \
	../sources/LocalitySensitiveHashing.cpp \
	../sources/NearNeighbors.cpp \
	../sources/Random.cpp \
	../sources/SelfTuning.cpp \
	../sources/testFloat.cp \
	../sources/Util.cpp \
	../sources/LSH.cpp

include_HEADERS = \
	../sources/LSH.h \
	../sources/BasicDefinitions.h \
	../sources/Geometry.h

# Linker options libTestProgram
libe2lshGen_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libe2lshGen_la_CPPFLAGS = -DREAL_DOUBLE -I$(top_srcdir)/../sources

ACLOCAL_AMFLAGS=-I m4