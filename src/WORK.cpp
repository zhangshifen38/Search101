//
// Created by AlexHoring on 2022/6/6.
//

#include "WORK.h"

int WORK::SEARCH() {

    list<string> listToDo;
    vector<CSVstorage> newsInfo;
    MapAVL<string, size_t> dict;
    SetAVL<string> separatorSet;
    std::chrono::milliseconds msTag,msTagEnd;
    double totalCost=0;
    do{
        ifstream inSp(IGNORE_WORD_PATH, ios::in);
        string sp;
        while (!inSp.eof()) {
            getline(inSp,sp);
            separatorSet.insert(sp);
        }
        inSp.close();
    }while(false);

    if(filesystem::exists(INITIAL_PATH)){
        filesystem::remove_all(INITIAL_PATH);
    }
    if(filesystem::exists(INVERTED_INDEX_LIST_PATH)){
        filesystem::remove_all(INVERTED_INDEX_LIST_PATH);
    }

    bool isChineseMode;
    char choice;
    cout << "Please select language / 请选择使用的语言: 0-English 1-中文（简体）" << endl;
    choice = cin.get();
    while (choice != '0' && choice != '1') {
        cout << "Your choice is " << choice << ", which is invalid." << endl;
        cout << "Please select language / 请选择使用的语言: 0-English 1-中文（简体）" << endl;
        cin >> choice;
    };
    isChineseMode = (choice == '1');
    cin.get();
    cout << "Your choice is " << (isChineseMode ? "中文（简体）." : "English.") << endl;

    //阶段1：生成临时索引文件
    msTag=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"\n[info] Start generate temporary index file and word number file..."<<endl;
    //读取CSV信息块
    CSVreader reader((isChineseMode ? NEWS_CHINESE_PATH : NEWS_PATH));
    while (!reader.end_of_file()) {
        listToDo.push_back(reader.get_sentense());
    }
    //读取新闻信息，并且生成词典、单词编号以及临时索引文件TemporaryIndex.dat，获取临时索引文件的大小
    size_t numOfData = Algos::read_and_store(listToDo, newsInfo, dict, separatorSet, isChineseMode);
    msTagEnd=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"[info] Success in "<<((double)(msTagEnd.count()-msTag.count())/1000)<<"s\n";
    totalCost+=((double)(msTagEnd.count()-msTag.count())/1000);

    char str[20];
    size_t count = 1;//记录段号
    //生成排序好的临时索引文件
    //阶段1：生成归并段，使用do{}while(false)限制作用域
    msTag=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"\n[info] Start generate sort runs file..."<<endl;
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
    } while (false);
    msTagEnd=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"[info] Success in "<<((double)(msTagEnd.count()-msTag.count())/1000)<<"s\n";
    totalCost+=((double)(msTagEnd.count()-msTag.count())/1000);
    //阶段2：归并段合并成排好序的临时索引文件。
    msTag=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"\n[info] Start generate sorted temporary index file..."<<endl;
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
        while ((*dataMess)[(*CMPArray)[0]].key.first != 99999999) {
            int q = (*CMPArray)[0];
            KeyType mini = (*dataMess)[q].key;
            writeToFinalData << mini.first << ' ' << mini.second << endl;
            countTotality++;
            if ((*dataMess)[q].filePoint.peek() == EOF) {
                (*dataMess)[q].key.first = (*dataMess)[q].key.second = 99999999;
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
    } while (false);
    msTagEnd=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"[info] Success in "<<((double)(msTagEnd.count()-msTag.count())/1000)<<"s\n";
    totalCost+=((double)(msTagEnd.count()-msTag.count())/1000);

    //生成倒排索引，通过根号分块使得对于大量数据的搜索复杂度降到根号级别
    size_t blockSize = sqrt(dict.size()), blockNumber = 0;
    string baseName = "/InvertedIndex_";
    string suffix = ".dat";
    string indexID;
    stringstream sio;
    msTag=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"\n[info] Start generate inverted index files..."<<endl;
    do {
        filesystem::create_directory(INVERTED_INDEX_LIST_PATH);
        ifstream readSortedItems;
        ofstream writeInvertedIndex;
        readSortedItems.open("../initial/FinalData.dat");
        sio << blockNumber;
        sio >> indexID;
        writeInvertedIndex.open(INVERTED_INDEX_LIST_PATH + baseName + indexID + suffix, ios::out);
        size_t currentID = 0, inID, inPage;
        size_t currentBlockNum = 0;
        pair<size_t, size_t> item;
        vector<pair<size_t, size_t> > invItems;
        while (!readSortedItems.eof()) {
            readSortedItems >> inID >> inPage;
            if (inID != currentID) {
                invItems.push_back(item);
                item = {inPage, 0};
                writeInvertedIndex << currentID << ' ';
                for (auto &i: invItems) {
                    writeInvertedIndex << i.first << ' ' << i.second << ' ';
                }
                writeInvertedIndex << '\n';
                currentID = inID;
                invItems.clear();
                ++currentBlockNum;
                if (currentBlockNum == blockSize) {
                    writeInvertedIndex.close();
                    writeInvertedIndex.clear(ios::goodbit);
                    ++blockNumber;
                    sio.clear(ios::goodbit);
                    sio << blockNumber;
                    sio >> indexID;
                    writeInvertedIndex.open(INVERTED_INDEX_LIST_PATH + baseName + indexID + suffix, ios::out);
                    currentBlockNum = 0;
                }
            }
            if (inPage != item.first) {
                invItems.push_back(item);
                item = {inPage, 0};
            }
            ++item.second;
        }
        invItems.push_back(item);
        writeInvertedIndex << currentID << ' ';
        for (auto &i: invItems) {
            writeInvertedIndex << i.first << ' ' << i.second << ' ';
        }
        writeInvertedIndex << '\n';
        writeInvertedIndex.close();
        readSortedItems.close();
    } while (false);
    msTagEnd=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout<<"[info] Success in "<<((double)(msTagEnd.count()-msTag.count())/1000)<<"s\n";
    totalCost+=((double)(msTagEnd.count()-msTag.count())/1000);

    cout << "\nInit successfully in total time "<<totalCost<<"s!\n\nType what you want to search: " << flush;
    string toSearch;
    getline(cin,toSearch);
    SetAVL<string> keyList;
    if(isChineseMode){
        vector<string> tk;
        Algos::ChineseCutter.Cut(toSearch,tk);
        for(string& st:tk){
            if(separatorSet.find(st)==separatorSet.end()){
                keyList.insert(st);
            }
        }
    }else{
        WordFilter filter;
        filter.set_sentence(std::move(toSearch));
        while (!filter.end_of_sentence()){
            keyList.insert(filter.get_word());
        }
    }
    vector<string> numberOrder;
    for(auto& st:keyList){
        numberOrder.emplace_back(st);
    }
    Algos::heap_sort(numberOrder.begin(),numberOrder.end(),[&dict](string &a,string &b)->bool {
        if(dict.find(a)==dict.end()){
            return false;
        }else if(dict.find(b)==dict.end()){
            return true;
        }
        return dict[a]<dict[b];
    });
    BinaryHeap<PageEvaluate> searchResult;
    do{
        string temp;
        MapAVL<size_t ,pair<size_t ,size_t > > findPage;
        ifstream readInvertedIndex;
        size_t curBlock,curIndex=0,pID,pCount,pIndex;
        readInvertedIndex.open(INVERTED_INDEX_LIST_PATH+baseName+"0"+suffix,ios::in);
        for(string &st:numberOrder){
            if(dict.find(st)==dict.end()){
                break;
            }
            size_t id=dict[st];
            if(id/blockSize!=curIndex){
                curIndex=id/blockSize;
                readInvertedIndex.close();
                readInvertedIndex.clear(ios::goodbit);
                sio.clear(ios::goodbit);
                sio<<curIndex;
                sio>>indexID;
                readInvertedIndex.open(INVERTED_INDEX_LIST_PATH+baseName+indexID+suffix,ios::in);
            }
            while(readInvertedIndex>>pIndex,pIndex!=id){
                getline(readInvertedIndex,temp);
            }
            sio.clear(ios::goodbit);
            getline(readInvertedIndex,temp);
            sio<<temp;
            while(!sio.eof()){
                sio>>pID>>pCount;
                findPage[pID].first++;
                findPage[pID].second+=pCount;
            }
        }
        readInvertedIndex.close();
        for(auto p:findPage){
            searchResult.push(PageEvaluate(p.first,p.second.second,p.second.first));
        }
    }while(false);

    cout<<"We found these:"<<'\n';
    while(!searchResult.empty()){
        newsInfo[searchResult.top().newsID].print();
        cout<<'\n';
        searchResult.pop();
    }

    return 0;
}
