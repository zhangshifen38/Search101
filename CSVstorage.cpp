//
// Created by 17207 on 2022/6/5.
//

#include "CSVstorage.h"



CSVstorage::CSVstorage(string &url, string &head, string &content): URL(url), head(head), content(content){}

void CSVstorage::print() {
    std::cout<<URL<<endl;
    std::cout<<head<<endl;
    std::cout<<content<<endl;
}

void CSVstorage::set_item(string url, string head, string content) {
    this->URL=url;
    this->head=head;
    this->content=content;
}

