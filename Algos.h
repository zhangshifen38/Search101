//
// Created by AlexHoring on 2022/6/4.
//

#ifndef SEARCH101_ALGOS_H
#define SEARCH101_ALGOS_H

//需要的头文件在这里补充
#include <iostream>
#include <list>
#include <vector>
#include "CSVstorage.h"
using namespace std;
/**
 * @author AlexHoring
 * @brief 所有的功能函数都在这里编写
 */
class Algos {
public:
    /**
     * @author AlexHoring
     * @brief 功能函数的编写示例：函数名前加static表静态，这里是定义，对应.cpp中写明实现。
     * @param sentence:示例函数的输出
     * @return none，可省略
     */
    static void sample_function(string sentence);
    /**
     * @author Hz
     * @brief  list容器ListToDo依次存放有网页URL（一行），网页标题（一行），网页内容（n行），分别将这三个内容存放进csvStorageList中的每个CSVstorage
     * @param listToDo:装有string的list容器，每个string是空串，或者连续是URL,标题，内容
     * @param csvStorageList:装有CSVstorage的list容器
     */
    static void read_and_store(std::list<string> &listToDo, std::vector<CSVstorage> &csvStorageList);
private:
    /**
     * @author Hz
     * @brief  工具，查找str字符串是否以prefix字符串开头
     * @param str:被查找的字符串
     * @param prefix:查找的开头
     * @return
     */
    static bool start_with(std::string &str, const std::string &prefix) ;
};


#endif //SEARCH101_ALGOS_H
