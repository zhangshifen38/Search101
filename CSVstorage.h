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
    CSVstorage()=default;
    /**
     * @author AlexHoring
     * @brief 带参构造函数
     * @param url :网页项目的URL
     * @param head :网页项目的标题
     * @param content :网页项目的内容
     */
    CSVstorage(string &url, string &head, string &content);
    /**
     * @author AlexHoring
     * @brief 设置网页信息类的内容
     * @param url :网页项目的URL
     * @param head :网页项目的标题
     * @param content :网页项目的内容
     */
    void set_item(string url,string head,string content);
    /**
     * @author Hz
     * @brief 测试用，打印URL，标题和正文
     */
    void print();
    string URL;     //网页URL
    string head;    //网页标题
    string content; //网页正文
};


#endif //SEARCH101_CSVSTORAGE_H
