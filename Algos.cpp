//
// Created by AlexHoring on 2022/6/4.
//

#include "Algos.h"
#include "BinaryHeap.h"

void Algos::sample_function(string sentence) {
    std::cout << "Sample sentence: " << sentence << std::endl;
}

void Algos::read_and_store(std::list<string> &listToDo, std::vector<CSVstorage> &csvStorageList) {
    string URL,head,content;
    int count = 0;//用来标志当前录入字符串是URL（3）还是标题（2）还是正文（1）
    std::string http = "http";
    for (auto item: listToDo) {
        if (start_with(item, http)) {
            count = 3;
        }//如果找到以http开头的字符串，则当前位置是URL，下一位置是标题，在下一位置是正文
        switch (count) {
            case 3:
                URL = item;
                count--;
                break;
            case 2:
                head = item;
                count--;
                break;
            case 1:
                content = item;
                count--;
                csvStorageList.emplace_back(CSVstorage(URL,head,content));
        }
    }
}

bool Algos::start_with(string &str, const string &prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}


