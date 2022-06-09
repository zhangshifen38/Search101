//
// Created by AlexHoring on 2022/6/5.
//

#ifndef SEARCH101_WORK_H
#define SEARCH101_WORK_H

#include <iostream>
#include <list>
#include <utility>
#include <fstream>
#include <filesystem>
#include "CSVreader.h"
#include "CSVstorage.h"
#include "Algos.h"
#include "WordFilter.h"
#include "SetAVL.h"
//will be removed later
#include <algorithm>
#include <map>

using namespace std;

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
