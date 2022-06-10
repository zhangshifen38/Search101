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
#include "MapAVL.h"
#include<iostream>
#include<fstream>
#include<vector>
#include <utility>
#include "ENTITY.h"
//will be removed later
#include <algorithm>
#include <map>


#define MAXIUM -1
#define endSymbol -1	//归并段结束标志
#define CAPACITY 10000  //内存工作区可容纳的记录个数
#define numOfData 1588528 //文件中的记录数量
using namespace std;

typedef pair<int,int> KeyType;	//定义关键字类型为整形,first存单词ID，second存新闻编号

typedef struct{
    KeyType key; //关键字项
}RedType;//数据记录项

typedef int loserTree[CAPACITY];//用于选取最小值的败者树

typedef struct{
    RedType rec;//记录
    KeyType key;//关键字
    int mergeNum;//所属归并段的段号
}RedNode,WorkArea[CAPACITY];//数据节点和用于得到归并段的工作区

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
    /**
     * @author Hz
     * @param ls ,用于得到最小值的败者树
     * @param wa，工作区
     * @param q，指示要加入败者树的元素的位置
     * @brief 用于调整败者树，从wa[q]起到败者树的根比较选择MINIMAX记录，最终ls[0]为最小元素在工作区中的的位置
     */
    static void SelectMinMax(loserTree &ls,WorkArea &wa,int q);
    /**
     * @author Hz
     * @param ls,用于得到最小值的败者树
     * @param wa，工作区
     * @param fi,用于从原始文件中读取数据的输入文件流
     * @brief 用于第一次从原始文件中读取数据进入工作区，建立败者树
     */
    static void ConstructLoserTree(loserTree &ls,WorkArea &wa,ifstream &fi);
    /**
     *
     * @param ls ,用于得到最小值的败者树
     * @param wa ，工作区
     * @param fi ,用于从原始文件中读取数据的输入文件流
     * @param counts，计数当前已经排序的数据项个数
     * @param rc，记录当前归并段序号
     * @param rmax，记录败者树最大归并段序号
     * @param fo,输出文件流，用于将数据输出到归并段文件中
     * @brief 用于得到一个归并段
     */
    static void GetMergeSection(loserTree &ls,WorkArea &wa,ifstream &fi,int &counts,int rc,int &rmax,ofstream &fo);

};

#endif //SEARCH101_WORK_H
