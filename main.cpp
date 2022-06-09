#include <iostream>
#include <functional>
#include "Algos.h"
#include "CSVreader.h"
#include "CSVstorage.h"
#include "BinaryHeap.h"
#include "WORK.h"
#include "WordFilter.h"
#include "AVLtree.h"
#include <vector>
using namespace std;

//template<class T>
//void display(T first,T end){
//    auto it=first;
//    while(it != end){
//        cout<<*it<<" ";
//        it++;
//    }
//}

int main() {
    //main函数暂时用于测试，日后我会补充完整功能。

//    BinaryHeap<int> bh;
//    bh.push(6);
//    bh.push(0);
//    bh.push(3);
//    bh.push(2);
//    while(!bh.empty()){
//        cout<<bh.top();
//        bh.pop();
//    }

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
