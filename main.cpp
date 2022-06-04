#include <iostream>
#include "Algos.h"
#include "CSVreader.h"
using namespace std;

int main() {
    //main函数暂时用于测试，日后我会补充完整功能。
    std::cout << "Hello, World!" << std::endl;
    Algos::sample_function("sample");   //函数调用
    CSVreader reader("news.csv");
    ofstream of("out.txt",ios::out);
    of<<reader.get_sentense()<<endl;
    of<<reader.get_sentense()<<endl;
    of<<reader.get_sentense()<<endl;
    return 0;
}
