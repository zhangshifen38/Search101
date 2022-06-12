//
// Created by AlexHoring on 2022/6/4.
//

#include "Algos.h"


void Algos::sample_function(string sentence) {
    std::cout << "Sample sentence: " << sentence << std::endl;
}

size_t Algos::read_and_store(std::list<string> &listToDo, std::vector<CSVstorage> &csvStorageList,
                             MapAVL<std::string, size_t> &dictionary, bool isChineseMode) {
    //extend by AlexHoring: 整合生成临时索引、单词编号的功能，返回临时索引文件中的项目数
    size_t itemNumber = 0;
    ofstream writeToTempIndex, writeToWordNumber;
    filesystem::create_directory(INITIAL_PATH); //创建initial路径
    writeToTempIndex.open(INITIAL_PATH + TEMP_INDEX_PATH, ios::out);    //打开临时索引存放文件
    writeToWordNumber.open(INITIAL_PATH + WORD_NUMBER_PATH, ios::out);  //打开单词编号存放文件
    cppjieba::Jieba filter(
            DICT_PATH,
            HMM_PATH,
            USER_DICT_PATH,
            IDF_PATH,
            STOP_WORD_PATH);    //中文分词工具类初始化

    string URL, head;
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
                count--;
                //直接将标题与新闻内容写入文件，返回写入临时索引的项目数
                itemNumber += (
                        isChineseMode
                        ? write_to_file_Chinese(filter, writeToTempIndex, writeToWordNumber, dictionary, head, item,
                                                csvStorageList.size())
                        : write_to_file(writeToTempIndex, writeToWordNumber, dictionary, head, item,
                                        csvStorageList.size())
                );
                //新闻存储类就不需要“正文内容”这个条目了。
                csvStorageList.emplace_back(CSVstorage(URL, head));
                break;
        }
    }
    writeToTempIndex << flush;
    writeToTempIndex.close();
    writeToWordNumber << flush;
    writeToWordNumber.close();
    return itemNumber;
}

bool Algos::start_with(string &str, const string &prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

size_t Algos::write_to_file(ofstream &writeToTempIndex, ofstream &writeToWordNumber, MapAVL<std::string, size_t> &dict,
                            std::string &head, std::string &content, size_t newsID) {
    static WordFilter filter;
    size_t itemNumber = 0;
    std::string wordFromSentence;
    //提取标题与正文的单词
    filter.set_sentence(head + " " + content);
    while (!filter.end_of_sentence()) {
        wordFromSentence = filter.get_word();
        if (dict.find(wordFromSentence) == dict.end()) {
            writeToWordNumber << wordFromSentence << ' ' << dict.size() << '\n';
            dict.insert({wordFromSentence, dict.size()});
        }
        writeToTempIndex << dict[wordFromSentence] << ' ' << newsID << '\n';
        ++itemNumber;
    }
    return itemNumber;
}

size_t
Algos::write_to_file_Chinese(cppjieba::Jieba &filter, ofstream &writeToTempIndex, ofstream &writeToWordNumber,
                             MapAVL<std::string, size_t> &dict, string &head, string &content, size_t newsID) {
    vector<std::string> words;
    size_t itemNumber = 0;
    //调用Jieba分词库对标题进行分词
    filter.Cut(head, words);
    for (auto &wordFromSentence: words) {
        if (dict.find(wordFromSentence) == dict.end()) {
            writeToWordNumber << wordFromSentence << ' ' << dict.size() << '\n';
            dict.insert({wordFromSentence, dict.size()});
        }
        ++itemNumber;
        writeToTempIndex << dict[wordFromSentence] << ' ' << newsID << '\n';
    }
    words.clear();
    //对正文进行分词
    filter.Cut(content, words);
    for (auto &wordFromSentence: words) {
        if (dict.find(wordFromSentence) == dict.end()) {
            writeToWordNumber << wordFromSentence << ' ' << dict.size() << '\n';
            dict.insert({wordFromSentence, dict.size()});
        }
        ++itemNumber;
        writeToTempIndex << dict[wordFromSentence] << ' ' << newsID << '\n';
    }
    return itemNumber;
}


