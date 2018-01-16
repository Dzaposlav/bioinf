cmake_minimum_required(VERSION 3.6)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall -Ofast -march=native -flto -freciprocal-math -fno-signed-zeros -fno-trapping-math -funroll-loops -fassociative-math")

set(SOURCE_FILES
        # sais
        src/sais.hpp

        )

add_executable(bioinf src/main.cpp ${SOURCE_FILES} src/main.cpp)
