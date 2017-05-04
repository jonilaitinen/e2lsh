CXX=g++
RM=rm -f

CPPFLAGS=-Wall -g -std=c++0x -DREAL_DOUBLE \
-I../sources

LDFLAGS=
LDLIBS=

SRCS= main.cpp ../sources/BucketHashing.cpp ../sources/Geometry.cpp ../sources/GlobalVars.cpp ../sources/LocalitySensitiveHashing.cpp ../sources/LSH.cpp ../sources/NearNeighbors.cpp ../sources/Random.cpp ../sources/SelfTuning.cpp ../sources/Util.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: test

test: $(OBJS)
	$(CXX) $(LDFLAGS) -o test $(OBJS) $(LDLIBS)

*.o: $(SRCS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) test
	$(RM) *.o
	$(RM) ../sources/*.o
