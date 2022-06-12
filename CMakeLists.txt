cmake_minimum_required(VERSION 3.22)
project(search101)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(search101 src/main.cpp src/CSVreader.cpp src/CSVreader.h src/Algos.cpp src/Algos.h src/CSVstorage.cpp src/CSVstorage.h src/WORK.cpp src/WORK.h src/WordFilter.cpp src/WordFilter.h src/AVLtree.h src/SetAVL.h src/MapAVL.h src/ENTITY.h src/ReplacementSelectionSort.h src/PageEvaluate.cpp src/PageEvaluate.h)
