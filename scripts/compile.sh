#!/usr/bin/env bash

SOURCE_FILES=" sais.hpp algorithms.cpp algorithms.h bitmask.cpp bitmask.h
wavelet.cpp wavelet.h alphabet_util.cpp alphabet_util.h main.cpp"

SOURCE_FILES="src/$(echo ${SOURCE_FILES} | sed -E 's/ / src\//g')"

FLAGS="-Ofast -march=native -flto -freciprocal-math -fno-signed-zeros -fno-trapping-math -funroll-loops -fassociative-math"

if [[ -f bioinf ]]; then
    rm -f bioinf
fi

echo ${SOURCE_FILES}

g++ -std=c++14 ${FLAGS} ${SOURCE_FILES} -o bioinf