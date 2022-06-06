#include <iostream>
#include "Algos.h"
#include "CSVreader.h"
#include "CSVstorage.h"
#include "BinaryHeap.h"
using namespace std;

int main() {
    //main函数暂时用于测试，日后我会补充完整功能。
    std::list<string> test;
    std::list<CSVstorage> test1;
    CSVstorage test2;
    test.push_back("http://en.people.cn/n3/2022/0524/c90000-10100455.html1");
    test.push_back("Govt takes steps to get economy back on track");
    test.push_back("ABCDEFE FAFAFEAFAFSAFEAFAFEAF");
    test.push_back("http://en.people.cn/n3/2022/0524/c90000-10100455.html2");
    test.push_back("Govt takes steps to get economy back on track");
    test.push_back("ABCDEFE FAFAFEAFAFSAFEAFAFEAF");
    test.push_back("http://en.people.cn/n3/2022/0524/c90000-10100455.html3");
    test.push_back("Govt takes steps to get economy back on track");
    test.push_back("ABCDEFE FAFAFEAFAFSAFEAFAFEAF");
    test.push_back("        ");
    test.push_back("http://en.people.cn/n3/2022/0524/c90000-10100455.html4");
    test.push_back("Govt takes steps to get economy back on track");
    test.push_back("ABCDEFE FAFAFEAFAFSAFEAFAFEAF");
    test.push_back("");
    test.push_back("http://en.people.cn/n3/2022/0524/c90000-10100455.html5");
    test.push_back("Govt takes steps to get economy back on track");
    test.push_back("ABCDEFE FAFAFEAFAFSAFEAFAFEAF");
    test.push_back("http://en.people.cn/n3/2022/0524/c90000-10100455.html6");
    test.push_back("Govt takes steps to get economy back on track");
    test.push_back("ABCDEFE FAFAFEAFAFSAFEAFAFEAF");
    Algos::read_and_store(test, test1);
    for(auto item:test1){
        item.print();
    }
//    std::cout << "Hello, World!" << std::endl;
//    Algos::sample_function("sample");   //函数调用
//    CSVreader reader("news.csv");
//    ofstream of("out.txt",ios::out);
//    of<<reader.get_sentense()<<endl;
//    of<<reader.get_sentense()<<endl;
//    of<<reader.get_sentense()<<endl;
    return 0;
}
