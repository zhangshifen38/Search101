//
// Created by AlexHoring on 2022/6/5.
//

#ifndef SEARCH101_WORK_H
#define SEARCH101_WORK_H

#include <iostream>
#include <list>
#include <cmath>
#include <utility>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include "CSVreader.h"
#include "CSVstorage.h"
#include "Algos.h"
#include "WordFilter.h"
#include "SetAVL.h"
#include "MapAVL.h"
#include<iostream>
#include<fstream>
#include<vector>
#include <utility>
#include "ENTITY.h"
#include "ReplacementSelectionSort.h"
#include "PageEvaluate.h"
//will be removed later

using namespace std;

//typedef struct{
//    RedType rec;//记录
//    KeyType key;//关键字
//    ifstream filePoint;//所属归并段的文件号
//}WorkAreaPlus[CAPACITY];//数据节点和用于得到归并段的工作区

/**
 * @author AlexHoring
 * @brief 主要的功能都被写在这里。
 */
class WORK {
public:
    /**
     * @author AlexHoring
     * @brief 就是main函数的内容
     * @return 状态码
     */
    static int SEARCH();

};

#endif //SEARCH101_WORK_H
