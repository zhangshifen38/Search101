cmake_minimum_required(VERSION 3.22)
project(search101)

set(CMAKE_CXX_STANDARD 17)

add_executable(search101 main.cpp CSVreader.cpp CSVreader.h Algos.cpp Algos.h CSVstorage.cpp CSVstorage.h WORK.cpp WORK.h WordFilter.cpp WordFilter.h AVLtree.h SetAVL.h)
