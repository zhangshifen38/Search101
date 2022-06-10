//
// Created by AlexHoring on 2022/6/6.
//

#include "WORK.h"

void WORK::SelectMinMax(loserTree &ls, WorkArea &wa, int q) {
        for(int t=(CAPACITY+q)/2,p=ls[t];t>0;t=t/2,p=ls[t]){
            if(wa[p].mergeNum<wa[q].mergeNum||(wa[p].mergeNum==wa[q].mergeNum)&&(wa[p].key.first)<wa[q].key.first){
                int temp=q;
                q=ls[t];
                ls[t]=temp;
            }
        }
        ls[0]=q;
}

void WORK::ConstructLoserTree(loserTree &ls, WorkArea &wa, ifstream &fi) {
    for(int i=0;i!=CAPACITY;++i){
        wa[i].key.first=wa[i].key.second=wa[i].mergeNum=ls[i]=0;//工作区,败者树初始化
    }

    for(int i=CAPACITY-1;i>=0;--i){//输入一个关键字
        fi>>wa[i].key.first;
        fi>>wa[i].key.second;
        wa[i].mergeNum=1;//段号为1
       SelectMinMax(ls,wa,i);//调整败者树
    }
}

void WORK::GetMergeSection(loserTree &ls, WorkArea &wa, ifstream &fi, int &counts, int rc, int &rmax,ofstream &fo) {
    int tmpKey;
    while(wa[ls[0]].mergeNum==rc){//同属于一个段，不需要切换到下一个段
        int q=ls[0];
        KeyType minimax=wa[q].key;
        fo<<minimax.first<<"\t\t"<<minimax.second<<endl;		//筛选出一个数据记录，输出
        ++counts;
        if(counts>=numOfData){wa[q].mergeNum=rmax+1;wa[q].key.first=wa[q].key.second=-1;}//全部读取完之后，则只需要消化败者树中剩余未输出的元素
        else{
            fi>>wa[q].key.first>>wa[q].key.second; //提取下一个数据记录
            if(wa[q].key.first<minimax.first){  //如果小于上一个筛选出的数据记录，则它属于下一段
                rmax=rc+1;
                wa[q].mergeNum=rmax;
            }
            else{
                wa[q].mergeNum=rc;//否则属于当前段
            }
        }
        SelectMinMax(ls,wa,q);  //调整败者树
    }
}


int WORK::SEARCH() {

    list<string> listToDo;
    vector<CSVstorage> newsInfo;
    CSVreader reader(NEWS_PATH);
    MapAVL<string ,size_t> dict;

    //读取CSV信息块
    while(!reader.end_of_file()){
        listToDo.push_back(reader.get_sentense());
    }

    //读取新闻信息，并且生成词典与临时索引文件TemporaryIndex.dat
    Algos::read_and_store(listToDo, newsInfo, dict);


    vector< pair< size_t,size_t > > tempIndex;
    vector< pair< size_t ,vector<size_t> > > invIndex;

    //-------------------------------------------------------------置换选择排序生成归并段
    filesystem::create_directory("../initial/data");     //创建存放归并段文件的文件夹
    ifstream dataIn("../initial/TemporaryIndex.dat");
    char str[20]="data%d.dat";
    int count=1;
    sprintf(str,"..\\initial\\data\\data%d.dat",count);
    ofstream out(str);
    WorkArea wa;
    loserTree ls;
    ConstructLoserTree(ls,wa,dataIn);//初建败者树
    int rc=1;//当前生成的初始化段的段号，
    int rmax=1;//败者树中最大的段号
    int counts=CAPACITY-1;
    while(rc<=rmax){//rc=rmax+1的时候标志输入文件的置换排序已经完成
        GetMergeSection(ls,wa,dataIn,counts,rc,rmax,out);//求得一个归并段
        count++;
        out.close();
        out.clear(ios::goodbit);
        sprintf(str,"..\\initial\\data\\data%d.dat",count);
        out.open(str);
        rc=wa[ls[0]].mergeNum;//设置下一个段的段号
    }
    //-------------------------------------------------------------置换选择排序生成归并段
    //待替换
    //sort(tempIndex.begin(),tempIndex.end());
    //tempIndex.erase(unique(tempIndex.begin(),tempIndex.end()),tempIndex.end());
    //生成倒排索引
//    for(auto& t:tempIndex){
//        if(invIndex.empty()||invIndex.back().first!=t.first){
//            invIndex.push_back({t.first,vector<size_t>()});
//        }
//        invIndex.back().second.push_back(t.second);
//    }
//    cout<<"init successfully!\n"<<endl;
//    //搜索核心步骤
//    cout<<"Type what you want to search:"<<flush;
//    string search;
//    getline(cin,search);
//    SetAVL<size_t> finds;
//    filter.set_sentence(std::move(search));
//    while(!filter.end_of_sentence()){   //对用户的输入进行分词
//        search=filter.get_word();
//        if(dict.find(search)!=dict.end()){
//            for(size_t st:invIndex[dict[search]].second){
//                finds.insert(st);
//            }
//        }
//    }
//    cout<<"We found :\n"<<endl; //输出结果
//    for(size_t i:finds){
//        cout<<"URL: "<<newsInfo[i].URL<<"\nTitle: "<<newsInfo[i].head<<'\n'<<endl;
//    }

    return 0;
}
