cmake_minimum_required(VERSION 3.22)
project(search101)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(search101 main.cpp CSVreader.cpp CSVreader.h Algos.cpp Algos.h CSVstorage.cpp CSVstorage.h WORK.cpp WORK.h WordFilter.cpp WordFilter.h AVLtree.h SetAVL.h MapAVL.h ENTITY.h ReplacementSelectionSort.h)
