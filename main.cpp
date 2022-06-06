#include <iostream>
#include "Algos.h"
#include "CSVreader.h"
#include "CSVstorage.h"
#include "BinaryHeap.h"
using namespace std;

int main() {
    //main函数暂时用于测试，日后我会补充完整功能。
    BinaryHeap<int> bh;
    bh.push(3);
    bh.push(9);
    bh.push(1);
    bh.push(0);
    while(!bh.empty()){
        cout<<bh.top()<<endl;
        bh.pop();
    }

    return 0;
}
