//
// Created by AlexHoring on 2022/6/6.
//

#include "WORK.h"

int WORK::SEARCH() {

    list<string> listToDo;
    vector<CSVstorage> newsInfo;
    CSVreader reader("../simplified_news.csv"); //简化版，数据较少，用以验证思路是否可行
    while(!reader.end_of_file()){
        listToDo.push_back(reader.get_sentense());  //读取信息块
    }
    Algos::read_and_store(listToDo,newsInfo);   //存储新闻信息

    map<string ,int> dict;  //待替换
    vector< pair< size_t,size_t > > tempIndex;
    vector< pair< size_t ,vector<size_t> > > invIndex;
    WordFilter filter;

    for(size_t i=0;i<newsInfo.size();++i){
        filter.set_sentence(std::move(newsInfo[i].head));
        while(!filter.end_of_sentence()){
            string words=filter.get_word();
            if(dict.find(words)==dict.end()){
                dict.insert({words,dict.size()});
            }
            tempIndex.emplace_back(dict[words],i);
        }
        filter.set_sentence(std::move(newsInfo[i].content));
        while(!filter.end_of_sentence()){
            string words=filter.get_word();
            if(dict.find(words)==dict.end()){
                dict.insert({words,dict.size()});
            }
            tempIndex.emplace_back(dict[words],i);
        }
    }
    //待替换
    sort(tempIndex.begin(),tempIndex.end());
    tempIndex.erase(unique(tempIndex.begin(),tempIndex.end()),tempIndex.end());
    //生成倒排索引
    for(auto& t:tempIndex){
        if(invIndex.empty()||invIndex.back().first!=t.first){
            invIndex.push_back({t.first,vector<size_t>()});
        }
        invIndex.back().second.push_back(t.second);
    }
    cout<<"init successfully!\n"<<endl;
    //搜索核心步骤
    cout<<"Type what you want to search:"<<flush;
    string search;
    getline(cin,search);
    SetAVL<size_t> finds;
    filter.set_sentence(std::move(search));
    while(!filter.end_of_sentence()){   //对用户的输入进行分词
        search=filter.get_word();
        if(dict.find(search)!=dict.end()){
            for(size_t st:invIndex[dict[search]].second){
                finds.insert(st);
            }
        }
    }
    cout<<"We found :\n"<<endl; //输出结果
    for(size_t i:finds){
        cout<<"URL: "<<newsInfo[i].URL<<"\nTitle: "<<newsInfo[i].head<<'\n'<<endl;
    }

    return 0;
}
