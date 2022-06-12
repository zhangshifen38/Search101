//
// Created by AlexHoring on 2022/6/10.
//

#ifndef SEARCH101_ENTITY_H
#define SEARCH101_ENTITY_H

#include <string>

//各种路径定义
const std::string NEWS_PATH = "../news.csv";
const std::string NEWS_CHINESE_PATH = "../newsChinese.csv";
const std::string INITIAL_PATH = "../initial";
const std::string TEMP_INDEX_PATH="/TemporaryIndex.dat";
const std::string WORD_NUMBER_PATH="/WordNumber.dat";
const std::string MERGE_SEGMENT_PATH="/data";
const std::string INVERTED_INDEX_LIST_PATH="../InvertedIndexList";

//Jieba分词的各功能词典所在路径
const std::string DICT_PATH = "../dict/jieba.dict.utf8";
const std::string HMM_PATH = "../dict/hmm_model.utf8";
const std::string USER_DICT_PATH = "../dict/user.dict.utf8";
const std::string IDF_PATH = "../dict/idf.utf8";
const std::string STOP_WORD_PATH = "../dict/stop_words.utf8";

const size_t CAPACITY=10000;

#endif //SEARCH101_ENTITY_H
