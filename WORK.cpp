//
// Created by AlexHoring on 2022/6/6.
//

#include "WORK.h"

//WorkAreaPlus dataMess;



int WORK::SEARCH() {

    list<string> listToDo;
    vector<CSVstorage> newsInfo;
    MapAVL<string ,size_t> dict;

    bool isChineseMode;
    char choice;
    cout<<"Please select language / 请选择使用的语言: 0-English 1-中文（简体）"<<endl;
    choice=cin.get();
    while(choice!='0'&&choice!='1'){
        cout<<"Your choice is "<<choice<<", which is invalid."<<endl;
        cout<<"Please select language / 请选择使用的语言: 0-English 1-中文（简体）"<<endl;
        cin>>choice;
    };
    isChineseMode=(choice=='1');
    cin.get();
    cout<<"Your choice is "<<(isChineseMode?"中文（简体）.":"English.")<<endl;
    CSVreader reader((isChineseMode?NEWS_CHINESE_PATH:NEWS_PATH));
    //读取CSV信息块
    while(!reader.end_of_file()){
        listToDo.push_back(reader.get_sentense());
    }
    //读取新闻信息，并且生成词典、单词编号以及临时索引文件TemporaryIndex.dat，获取临时索引文件的大小
    size_t numOfData=Algos::read_and_store(listToDo, newsInfo, dict, isChineseMode);
    char str[20];
    size_t count = 1;//记录段号

    do {
        //Hz:置换选择排序生成归并段
        filesystem::create_directory(INITIAL_PATH + MERGE_SEGMENT_PATH);     //创建存放归并段文件的文件夹
        ifstream dataIn(INITIAL_PATH + TEMP_INDEX_PATH);

        sprintf(str, "../initial/data/data%d.dat", count);
        ofstream out(str);
        ReplacementSelectionSort<CAPACITY> *sortRS = new ReplacementSelectionSort<CAPACITY>(numOfData);
        sortRS->ConstructLoserTree(dataIn);
        int rc = 1;       //当前生成的初始化段的段号，
        int rmax = 1;     //败者树中最大的段号
        size_t counts = CAPACITY - 1;
        while (rc <= rmax) {    //rc=rmax+1的时候标志输入文件的置换排序已经完成
            //求得一个归并段
            sortRS->GetMergeSection(dataIn, counts, rc, rmax, out);
            count++;
            out.close();
            out.clear(ios::goodbit);
            if (counts < numOfData + CAPACITY - 1) {
                sprintf(str, "../initial/data/data%d.dat", count);
                out.open(str);
            }//防止生成多余的一个空文件
            rc = sortRS->get_next_segment_number();      //设置下一个段的段号
        }
        delete sortRS;
        sortRS = nullptr;
    }while(false);

    do {
        //ZKY and HZ: 归并段多路归并为一个文件
        ofstream writeToFinalData;
        writeToFinalData.open("../initial/FinalData.dat", fstream::out);    //写入排好序临时索引文件FinalData.dat
        //AlexHoring: 在堆上分配内存，防止爆栈空间
        LoserTree<CAPACITY> *CMPArray = new LoserTree<CAPACITY>();
        WorkAreaPlus<CAPACITY> *dataMess = new WorkAreaPlus<CAPACITY>();

        for (size_t i = count - 1; i > 0; i--) {
            sprintf(str, "../initial/data/data%d.dat", i);
            (*dataMess)[i - 1].filePoint.open(str);
            (*dataMess)[i - 1].filePoint >> (*dataMess)[i - 1].key.first >> (*dataMess)[i - 1].key.second;
            Algos::SelectMin(*CMPArray, *dataMess, i - 1, count - 1);
        }
        int countTotality = 0;
        while ((*dataMess)[(*CMPArray)[0]].key.first != 99999) {
            int q = (*CMPArray)[0];
            KeyType mini = (*dataMess)[q].key;
            writeToFinalData << mini.first << ' ' << mini.second << endl;
            countTotality++;
            if ((*dataMess)[q].filePoint.peek() == EOF) {
                (*dataMess)[q].key.first = (*dataMess)[q].key.second = 99999;
            }//读完文件将其数值置为数值上界
            else {
                (*dataMess)[q].filePoint >> (*dataMess)[q].key.first >> (*dataMess)[q].key.second; //提取下一个数据记录
            }
            Algos::SelectMin(*CMPArray, *dataMess, q, count - 1);
        }
        for (size_t i = count - 1; i != 0; i--) {
            (*dataMess)[i - 1].filePoint.close();
        }
        writeToFinalData.close();
        delete CMPArray;
        delete dataMess;
        CMPArray = nullptr;
        dataMess = nullptr;
    }while(false);


    return 0;
}
