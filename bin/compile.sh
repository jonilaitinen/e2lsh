#!/bin/bash

OUT_DIR=bin
SOURCES_DIR=sources
OBJ_SOURCES="$SOURCES_DIR/BucketHashing.cpp \
            $SOURCES_DIR/Geometry.cpp \
            $SOURCES_DIR/LocalitySensitiveHashing.cpp \
            $SOURCES_DIR/Random.cpp \
            $SOURCES_DIR/Util.cpp \
            $SOURCES_DIR/GlobalVars.cpp \
            $SOURCES_DIR/SelfTuning.cpp \
            $SOURCES_DIR/NearNeighbors.cpp"

TEST_BUILDS="exactNNs \
            genDS \
            compareOutputs \
            genPlantedDS"

defineFloat=REAL_FLOAT

g++ -o $OUT_DIR/testFloat -DREAL_FLOAT $OBJ_SOURCES $SOURCES_DIR/testFloat.cpp -lm >/dev/null 2>&1 || defineFloat=REAL_DOUBLE

OPTIONS="-O3 -D$defineFloat"

g++ -o $OUT_DIR/LSHMain $OPTIONS $OBJ_SOURCES $SOURCES_DIR/LSHMain.cpp -lm

chmod g+rwx $OUT_DIR/LSHMain

for i in $TEST_BUILDS; do
   g++ -o ${OUT_DIR}/$i $OPTIONS ${SOURCES_DIR}/${i}.cpp $OBJ_SOURCES -lm; chmod g+rwx $OUT_DIR/${i}; 

done