//
// Created by AlexHoring on 2022/6/4.
//

#ifndef SEARCH101_CSVREADER_H
#define SEARCH101_CSVREADER_H

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

/**
 * @author AlexHoring
 * @brief 以分隔块为单位读取指定CSV文件的内容
 */
class CSVreader {
public:
    /**
     * @author AlexHoring
     * @brief 类的构造函数
     * @param path：待读取CSV文件的路径
     */
    CSVreader(string&& path);
    /**
     * @author AlexHoring
     * @brief 判断文件是否读完
     * @return true假如文件已经读完，反之false
     */
    bool end_of_file();
    /**
     * @author AlexHoring
     * @brief 每次调用，获取一个分隔块的内容
     * @return 字符串，包含CSV文件下一个分隔块的所有内容
     */
    string get_sentense();
private:
    ifstream fileIn;
    int state;
    char readBuffer;
    bool isBufferFull;
    /**
     * @author AlexHoring
     * @brief 每次调用时，返回文件中的下一个字符，对CSV文件的读取操作以分割块为单位，因此单个字符读取函数不公开
     * @return 一个CSV文件里的字符
     */
    char get_char();
};


#endif //SEARCH101_CSVREADER_H
