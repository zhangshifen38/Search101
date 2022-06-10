#include <iostream>
#include <functional>
#include "Algos.h"
#include "CSVreader.h"
#include "CSVstorage.h"
#include "BinaryHeap.h"
#include "WORK.h"
#include "WordFilter.h"
#include "AVLtree.h"
#include "MapAVL.h"
#include "cppjieba/Jieba.hpp"
#include <vector>
using namespace std;

int main() {
    //main函数暂时用于测试，日后我会补充完整功能。

//    CSVreader vreader(NEWS_CHINESE_PATH);
//
//    for(int i=1;i<10;i++){
//        string st;
//        do{
//            st=vreader.get_sentense();
//        }while(st=="");
//        cout<<st<<endl;
//    }

    //调试模块的时候将下面的语句注释掉，将最后一句注释取消。调试功能逻辑的时候反之。
    return WORK::SEARCH();
    return 0;
}
