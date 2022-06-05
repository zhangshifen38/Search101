//
// Created by 17207 on 2022/6/5.
//

#include "CSVstorage.h"

CSVstorage::CSVstorage() {
}

void CSVstorage::print() {
    std::cout<<URL<<endl;
    std::cout<<head<<endl;
    std::cout<<content<<endl;
}

bool  CSVstorage::startsWith(std::string &str, const std::string &prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

void CSVstorage::readAndStrore(std::list<string> listToDo, std::list<CSVstorage> &csvStorageList) {
    CSVstorage tmp;
    int count=0;//用来标志当前录入字符串是URL（3）还是标题（2）还是正文（1）
    std::string http="http";
    for(auto item:listToDo){
        if(startsWith(item,http)){
            count=3;
        }//如果找到以http开头的字符串，则当前位置是URL，下一位置是标题，在下一位置是正文
        switch(count){
            case 3:{
                   tmp.URL=item;
                   count--;
               }
                break;
            case 2:{
                    tmp.head=item;
                    count--;
            }
            break;
            case 1:{
                    tmp.content=item;
                    count--;
                    csvStorageList.push_back(tmp);
            }
        }
    }
}
