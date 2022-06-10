//
// Created by AlexHoring on 2022/6/4.
//

#include "Algos.h"


void Algos::sample_function(string sentence) {
    std::cout << "Sample sentence: " << sentence << std::endl;
}

void Algos::read_and_store(std::list<string> &listToDo, std::vector<CSVstorage> &csvStorageList,
                           MapAVL<std::string, size_t> &dictionary) {
    //extend by AlexHoring: 整合生成临时索引的功能
    ofstream writeToTempIndex;
    filesystem::create_directory(INITIAL_PATH);
    writeToTempIndex.open(INITIAL_PATH+TEMP_INDEX_PATH,ios::out);

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
                //content=item;
                count--;
                //直接将标题与新闻内容写入文件
                write_to_temporary_index(writeToTempIndex,dictionary,head,item,csvStorageList.size());
                //新闻存储类就不需要“正文内容”这个条目了。
                csvStorageList.emplace_back(CSVstorage(URL,head,content));
                break;
        }
    }
    writeToTempIndex<<flush;
    writeToTempIndex.close();
}

bool Algos::start_with(string &str, const string &prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

void Algos::write_to_temporary_index(ofstream &writeToTempIndex, MapAVL<std::string, size_t> &dict, std::string &head,
                                     std::string &content, size_t newsID) {
    static WordFilter filter;
    std::string wordFromSentence;
    //提取标题与正文的单词
    filter.set_sentence(head+" "+content);
    while(!filter.end_of_sentence()){
        wordFromSentence=filter.get_word();
        if(dict.find(wordFromSentence)==dict.end()){
            dict.insert({wordFromSentence,dict.size()});
        }
        writeToTempIndex<<dict[wordFromSentence]<<' '<<newsID<<'\n';
    }
}


