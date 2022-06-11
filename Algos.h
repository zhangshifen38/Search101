//
// Created by AlexHoring on 2022/6/4.
//

#ifndef SEARCH101_ALGOS_H
#define SEARCH101_ALGOS_H

//需要的头文件在这里补充
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <filesystem>
#include <functional>
#include "CSVstorage.h"
#include "WordFilter.h"
#include "MapAVL.h"
#include "BinaryHeap.h"
#include "cppjieba/Jieba.hpp"
#include "ENTITY.h"

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
    static void read_and_store(std::list<string> &listToDo, std::vector<CSVstorage> &csvStorageList,
                               MapAVL<std::string, size_t> &dictionary, bool isChineseMode);

    static void
    write_to_file(ofstream &writeToTempIndex, ofstream &writeToWordNumber, MapAVL<std::string, size_t> &dict,
                  std::string &head, std::string &content, size_t newsID);

    static void write_to_file_Chinese(cppjieba::Jieba &filter, ofstream &writeToTempIndex, ofstream &writeToWordNumber,
                                      MapAVL<std::string, size_t> &dict, string &head, string &content, size_t newsID);

    /**
     * @author TL
     * @brief  heap_sort实现一个堆排序，直接排好序，没有返回值。
     * @param begin可以理解为头部迭代器，end可以理解为尾部迭代器，makeGreaterSort为一个自定义的重构排序函数
     * @return none
     */
    template<class _iterator>
    void heap_sort(_iterator begin,_iterator end){
        build_heap(begin,end);
        for(auto it = end - 1;it >= begin;it--){
            swap(*it ,*begin);
            Algos::heap_realign(begin,it,begin);
        }
    }
    /**
     * @author TL
     * @brief  build_heap实现构造大根堆，没有返回值。
     * @param begin 是传入的开始迭代器，end是传入时的迭代器
     */
    template<class _iterator>
    void build_heap(_iterator begin,_iterator end){
        int lastNode = end - begin - 1;
        int parent = (lastNode - 1)/2;
        auto tempBegin = begin + parent;
        for( ;tempBegin >= begin;tempBegin--){
            heap_realign(begin,end,tempBegin);
        }
    }
    /**
     * @author TL
     * @brief  heap_realign重新构造剩余的大根堆，没有返回值。
     * @param begin 是传入的开始迭代器，end是传入时的迭代器
     */
    template<class _iterator>
    void heap_realign(_iterator begin,_iterator end,_iterator parent){
        if(parent >= end)
            return;
        int leftChild = (parent - begin)*2 + 1;
        int rightChild = (parent - begin)*2 +2;
        int max = parent - begin;
        if((leftChild < (end - begin)) && (*(begin + leftChild) > *(begin + max))){
            max = leftChild;
        }
        if((rightChild < (end - begin))&&(*(begin + rightChild) > *(begin + max))){
            max = rightChild;
        }
        if(max != parent - begin){
            swap(*(begin + max),*(parent));
            heap_realign(begin,end,begin + max);
        }
    }

    /**
     * @author TL
     * @brief  heap_sort实现一个堆排序，直接排好序，没有返回值。
     * @param begin可以理解为头部迭代器，end可以理解为尾部迭代器，compare为一个自定义排序仿函数
     * @return none
     */
    template<class _iterator,typename _Compare>
    void heap_sort(_iterator begin,_iterator end,_Compare compare){
        build_heap(begin,end,compare);
        for(auto it = end - 1;it >= begin;it--){
            swap(*it ,*begin);
            Algos::heap_realign(begin,it,begin,compare);
        }
    }
    /**
     * @author TL
     * @brief  build_heap建立一个堆，没有返回值。
     * @param begin可以理解为头部迭代器，end可以理解为尾部迭代器，compare为一个自定义排序仿函数
     * @return none
     */
    template<class _iterator,typename _Compare>
    void build_heap(_iterator begin,_iterator end,_Compare compare){
        int lastNode = end - begin - 1;
        int parent = (lastNode - 1)/2;
        auto tempBegin = begin + parent;
        for( ;tempBegin >= begin;tempBegin--){
            heap_realign(begin,end,tempBegin,compare);
        }
    }
    /**
     * @author TL
     * @brief  heap_realign实现堆的比较大小，没有返回值。
     * @param begin可以理解为头部迭代器，end可以理解为尾部迭代器，compare为一个自定义排序仿函数
     * @return none
     */
    template<class _iterator,typename _Compare>
    void heap_realign(_iterator begin,_iterator end,_iterator parent,_Compare compare){
        if(parent >= end)
            return;
        int leftChild = (parent - begin)*2 + 1;
        int rightChild = (parent - begin)*2 +2;
        int max = parent - begin;
        if((leftChild < (end - begin)) && compare((begin + max),(begin + leftChild))){
            max = leftChild;
        }
        if((rightChild < (end - begin)) && compare((begin + max),(begin + rightChild))){
            max = rightChild;
        }
        if(max != parent - begin){
            swap(*(begin + max),*(parent));
            heap_realign(begin,end,begin + max,compare);
        }
    }




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

/**
     * @author TL
     * @brief  lessCompare定义一个小于号的仿函数，
     * @param 重构括号，括号里的第一个first为比较的第一个迭代器，第二个second为比较的第二个迭代器
     */
class lessCompare {
public:
    template<typename _iterator>
    bool operator()(_iterator first, _iterator second) {
        return *(first) < *(second);
    }
};
/**
     * @author TL
     * @brief  lessCompare定义一个大于号的仿函数，
     * @param 重构括号，括号里的第一个first为比较的第一个迭代器，第二个second为比较的第二个迭代器
     */
class greaterCompare {
public:
    template<typename _iterator>
    bool operator()(_iterator first, _iterator second) {
        return *(first) > *(second);
    }
};
#endif //SEARCH101_ALGOS_H
