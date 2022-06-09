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
#include <vector>
using namespace std;

int main() {
    //main函数暂时用于测试，日后我会补充完整功能。


//    int a[]={10,6,8,5,4,4,1,2,1};
//    vector<int> v1(a,a+9);
//    display(v1.begin(),v1.end());
//    Algos aa;
//    greaterCompare compare;
//    cout<<"heap_sort"<<endl;
//    //aa.heap_sort(v1.begin(),v1.end());
//    aa.heap_sort(v1.begin(),v1.end(),compare);
//    //Algos::heap_sort(v1.begin(),v1.end());
//    display(v1.begin(),v1.end());

    AVLtree<int> av;
    for(int i=1;i<16;++i){
        av.insert(i);
        if(i==3||i==7||i==15){
            av.print();
        }
    }

    cout<<(*av.begin())<<endl;
    MapAVL<int,int> mp;
    mp[1]=2;
    mp[2]=3;
    mp[3]=4;
    mp[4]=5;
    cout<<mp[3]<<endl;
    cout<<mp[5]<<endl;
    //调试模块的时候将下面的语句注释掉，将最后一句注释取消。调试功能逻辑的时候反之。
    //return WORK::SEARCH();
    return 0;
}
