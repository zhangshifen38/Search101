//
// Created by AlexHoring on 2022/6/6.
//

#ifndef SEARCH101_WORDFILTER_H
#define SEARCH101_WORDFILTER_H

#include <string>
#include <cctype>

enum FilterState{
    READY,PICKING,FILTED
};


/**
 * @author AlexHoring
 * @brief 从一个字符串中根据分隔符提取单词。
 */
class WordFilter {
public:
    WordFilter()=default;

    /**
     * @author AlexHoring
     * @brief 判断字符串是否读到结尾
     * @return true if read til the end of string
     */
    bool end_of_sentence();

    /**
     * @author AlexHoring
     * @brief 从句子中识别一个单词
     * @return 包含单词的字符串，其中单词全部被转换为小写
     */
    std::string get_word();

    /**
     * @author AlexHoring
     * @brief 设置需要读取的字符串
     * @param sentence 需要提取单词的字符串
     */
    void set_sentence(std::string &&sentence);
private:
    std::string stream;
    size_t index;
    FilterState state;
};


#endif //SEARCH101_WORDFILTER_H
