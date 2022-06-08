#include <iostream>
#include "Algos.h"
#include "CSVreader.h"
#include "CSVstorage.h"
#include "BinaryHeap.h"
#include "WORK.h"
#include "WordFilter.h"
#include "AVLtree.h"
using namespace std;

int main() {
    //main函数暂时用于测试，日后我会补充完整功能。
//    AVLtree<int> av;
//    for(int i=1;i<16;++i){
//        av.insert(i);
//        if(i==3||i==7||i==15){
//            av.print();
//        }
//    }
//    av.erase(av.find(1));
//    av.erase(av.find(3));
//    av.erase(av.find(2));
//    av.print();
//    av.insert(3);
//    av.insert(1);
//    av.insert(2);
//    av.print();
//    av.erase(av.find(8));
//    av.print();
    //调试模块的时候将下面的语句注释掉，将最后一句注释取消。调试功能逻辑的时候反之。
    return WORK::SEARCH();
    //return 0;
}
