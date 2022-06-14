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
#include "ReplacementSelectionSort.h"
#include "SetAVL.h"

using namespace std;
/**
 * @author AlexHoring
 * @brief 所有的功能函数都在这里编写
 */
class Algos {
public:
    //中文分词库的初始化较为耗时，因此设置为静态变量
    static cppjieba::Jieba ChineseCutter;
    /**
     * @author AlexHoring
     * @brief 功能函数的编写示例：函数名前加static表静态，这里是定义，对应.cpp中写明实现。
     * @param sentence:示例函数的输出
     * @return none，可省略
     */
    static void sample_function(string sentence);

    /**
     * @author Hz
     * @param q，指示要加入败者树的元素的位置
     * @brief 用于调整败者树，从wa[q]起到败者树的根比较选择MINI记录，最终ls[0]为最小元素在工作区中的的位置
     */
    template<size_t Capacity>
    static void SelectMin(LoserTree<Capacity> &loserTree,WorkAreaPlus<Capacity> &workAreaPlus, int q, int count);
    /**
     * @authors Hz,AlexHoring
     * @brief  list容器ListToDo依次存放有网页URL，网页标题，分别存放进csvStorageList中的每个CSVstorage,并创建临时索引与单词编号文件。
     * @param listToDo:装有string的list容器，每个string是空串，或者连续是URL、标题、内容
     * @param csvStorageList:装有CSVstorage的list容器
     * @param dictionary 查询单词是否出现的容器
     * @param isChineseMode 是否中文模式的判断变量
     */
    static size_t read_and_store(std::list<string> &listToDo, std::vector<CSVstorage> &csvStorageList,
                                 MapAVL<std::string, size_t> &dictionary, SetAVL<string> &separatorSet,
                                 bool isChineseMode);

    /**
     * @author AlexHoring
     * @brief 写入英文的未排序的临时索引文件与单词编号文件
     * @param writeToTempIndex 指向临时索引文件的文件流
     * @param writeToWordNumber 指向单词编号文件的文件流
     * @param dict 记录单词是否出现的map对象
     * @param head 网页标题
     * @param content 网页正文
     * @param newsID 新闻网页的编号
     */
    static size_t
    write_to_file(ofstream &writeToTempIndex, ofstream &writeToWordNumber, MapAVL<std::string, size_t> &dict,
                  std::string &head, std::string &content, size_t newsID);

    /**
     * @author AlexHoring
     * @brief 写入中文的未排序临时索引文件与单词编号文件
     * @param ChineseCutter Jieba分词工具的对象实例
     * @param writeToTempIndex 指向临时索引文件的文件流
     * @param writeToWordNumber 指向单词编号文件的文件流
     * @param dict 记录单词是否出现的map对象
     * @param head 网页标题
     * @param content 网页正文
     * @param newsID 新闻网页的编号
     */
    static size_t
    write_to_file_Chinese(ofstream &writeToTempIndex, ofstream &writeToWordNumber, MapAVL<std::string, size_t> &dict,
                          string &head, string &content, size_t newsID, SetAVL<string> &separatorSet);

    /**
     * @author TL
     * @brief  heap_sort实现一个堆排序，直接排好序，没有返回值。
     * @param begin 可以理解为头部迭代器。
     * @param end 可以理解为尾部迭代器.
     * @param makeGreaterSort 为一个自定义的重构排序函数
     * @return none
     */
    template<class _iterator>
    static void heap_sort(_iterator begin,_iterator end){
        if(begin==end){
            return;
        }
        build_heap(begin,end);
        for(auto it = end - 1;it >= begin;it--){
            swap(*it ,*begin);
            Algos::heap_realign(begin,it,begin);
        }
    }

    /**
     * @author TL
     * @brief  heap_sort实现一个堆排序，直接排好序。
     * @param begin 头部迭代器
     * @param end 尾部迭代器
     * @param compare 一个自定义排序仿函数
     */
    template<class _iterator,typename _Compare>
    static void heap_sort(_iterator begin,_iterator end,_Compare compare){
        if(begin==end){
            return;
        }
        build_heap(begin,end,compare);
        for(auto it = end - 1;it >= begin;it--){
            swap(*it ,*begin);
            Algos::heap_realign(begin,it,begin,compare);
        }
    }



private:
    /**
     * @author Hz
     * @brief  工具，查找str字符串是否以prefix字符串开头
     * @param str:被查找的字符串
     * @param prefix:查找的开头
     * @return true如果以prefix开头，否则false
     */
    static bool start_with(std::string &str, const std::string &prefix) ;
    /**
     * @author TL
     * @brief  build_heap实现构造大根堆，没有返回值。
     * @param begin 是传入的开始迭代器，end是传入时的迭代器
     */
    template<class _iterator>
    static void build_heap(_iterator begin,_iterator end){
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
    static void heap_realign(_iterator begin,_iterator end,_iterator parent){
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
     * @brief  build_heap建立一个堆，没有返回值。
     * @param begin可以理解为头部迭代器，end可以理解为尾部迭代器，compare为一个自定义排序仿函数
     * @return none
     */
    template<class _iterator,typename _Compare>
    static void build_heap(_iterator begin,_iterator end,_Compare compare){
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
    static void heap_realign(_iterator begin,_iterator end,_iterator parent,_Compare compare){
        if(parent >= end)
            return;
        int leftChild = (parent - begin)*2 + 1;
        int rightChild = (parent - begin)*2 +2;
        int max = parent - begin;
        if((leftChild < (end - begin)) && compare(*(begin + max),*(begin + leftChild))){
            max = leftChild;
        }
        if((rightChild < (end - begin)) && compare(*(begin + max),*(begin + rightChild))){
            max = rightChild;
        }
        if(max != parent - begin){
            swap(*(begin + max),*(parent));
            heap_realign(begin,end,begin + max,compare);
        }
    }
};


template<size_t Capacity>
void Algos::SelectMin(LoserTree<Capacity> &loserTree, WorkAreaPlus<Capacity> &workAreaPlus, int q, int count){
    for(int t=(count+q)/2,p=loserTree[t];t>0;t=t/2,p=loserTree[t]){     //t为新加入节点的双亲节点的位置
        if(workAreaPlus[p].key.first < workAreaPlus[q].key.first || (workAreaPlus[p].key.first == workAreaPlus[q].key.first) && (workAreaPlus[p].key.second) < workAreaPlus[q].key.second){
            int temp=q;
            q=loserTree[t];        //q始终存放胜者的位置
            loserTree[t]=temp;
        }               //段号小的或者短号相等但是关键字小的为胜者
    }
    loserTree[0]=q;    //loserTree[0]为最终胜者的位置，即最小值的位置
}



#endif //SEARCH101_ALGOS_H
