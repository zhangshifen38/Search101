//
// Created by 17207 on 2022/6/5.
//

#ifndef SEARCH101_CSVSTORAGE_H
#define SEARCH101_CSVSTORAGE_H

#include <string>
#include <fstream>
#include <iostream>
#include <list>

using  namespace  std;
/**
 * @author Hz
 * @brief 存储网页的url，标题和正文
 */
class CSVstorage {
public:
    CSVstorage();
    /**
     * @author Hz
     * @brief  list容器ListToDo依次存放有网页URL（一行），网页标题（一行），网页内容（n行），分别将这三个内容存放进csvStorageList中的每个CSVstorage
     * @param listToDo:装有string的list容器，每个string是空串，或者连续是URL,标题，内容
     * @param csvStorageList:装有CSVstorage的list容器
     */
    void readAndStrore(std::list<string>listToDo,std::list<CSVstorage> &csvStorageList);
    /**
     * @author Hz
     * @brief  工具，查找str字符串是否以prefix字符串开头
     * @param str:被查找的字符串
     * @param prefix:查找的开头
     * @return
     */
    bool startsWith(std::string &str, const std::string &prefix) ;
    /**
     * @author Hz
     * @brief 测试用，打印URL，标题和正文
     */
    void print();
private:
    string URL;     //网页URL
    string head;    //网页标题
    string content; //网页正文
};


#endif //SEARCH101_CSVSTORAGE_H
