//
// Created by 17207 on 2022/6/5.
//

#include "CSVstorage.h"



CSVstorage::CSVstorage(string &url, string &head): URL(url), head(head){}

void CSVstorage::print() {
    std::cout<<URL<<endl;
    std::cout<<head<<endl;
}

void CSVstorage::set_item(string url, string head) {
    this->URL=url;
    this->head=head;

}

