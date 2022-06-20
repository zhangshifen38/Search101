//
// Created by AlexHoring on 2022/6/11.
//

#ifndef SEARCH101_REPLACEMENTSELECTIONSORT_H
#define SEARCH101_REPLACEMENTSELECTIONSORT_H

#include <array>
#include <utility>
#include <fstream>

const int MAXIUM=-1;     //无穷大

//用于选取最小值的败者树的非终端节点，里面的值是某节点在工作区中的位置序号，[0]位置是胜者
template<size_t Capacity>
using LoserTree = std::array<int,Capacity>;

//定义关键字类型为整形,first存单词ID，second存新闻编号
typedef std::pair<int,int> KeyType;


//数据节点
struct RedNode{
    KeyType key;    //关键字
    int mergeNum;   //所属归并段的段号
};

//数据节点
struct RedNodePlus{
    KeyType key;//关键字
    std::ifstream filePoint;//所属归并段的文件号
};

//用于得到归并段的工作区
template<size_t Capacity>
using WorkAreaPlus = std::array<RedNodePlus,Capacity>;

//用于得到归并段的工作区
template<size_t Capacity>
using WorkArea = std::array<RedNode,Capacity>;

template<size_t Capacity>
class ReplacementSelectionSort {
public:

    ReplacementSelectionSort()=default;
    ReplacementSelectionSort(size_t numOfData);
    /**
     * @author Hz
     * @param q，指示要加入败者树的元素的位置
     * @brief 用于调整败者树，从wa[q]起到败者树的根比较选择MINIMAX记录，最终ls[0]为最小元素在工作区中的的位置
     */
    void SelectMinMax(int q);

    /**
     * @author Hz
     * @param fi 用于从原始文件中读取数据的输入文件流
     * @brief 用于第一次从原始文件中读取数据进入工作区，建立败者树
     */
    void ConstructLoserTree(std::ifstream &fi);

    /**
     * @author Hz
     * @brief 用于得到一个归并段
     * @param fi 用于从原始文件中读取数据的输入文件流
     * @param counts 计数当前已经排序的数据项个数
     * @param rc 记录当前归并段序号
     * @param rmax 记录败者树最大归并段序号
     * @param fo 输出文件流，用于将数据输出到归并段文件中
     */
    void GetMergeSection(std::ifstream &fi, size_t &counts, int rc, int &rmax, std::ofstream &fo);

    int nextSegNumber();

private:
    LoserTree<Capacity> loserTree;
    WorkArea<Capacity> workArea;
    int numOfData;
};

template<size_t Capacity>
void ReplacementSelectionSort<Capacity>::SelectMinMax(int q) {
    for(int t=(Capacity+q)/2,p=loserTree[t]; t > 0; t= t / 2, p=loserTree[t]){//t为新加入节点的双亲节点的位置
        if((workArea[p].mergeNum < workArea[q].mergeNum) || ((workArea[p].mergeNum == workArea[q].mergeNum) && (workArea[p].key.first < workArea[q].key.first))||((workArea[p].mergeNum == workArea[q].mergeNum) && (workArea[p].key.first==workArea[q].key.first)&&(workArea[p].key.second<workArea[q].key.second))){
            int temp=q;
            q=loserTree[t];//q始终存放胜者的位置
            loserTree[t]=temp;
        }//段号小的或者短号相等但是关键字小的为胜者
    }
    loserTree[0]=q;//loserTree[0]为最终胜者的位置，即最小值的位置
}

template<size_t Capacity>
void ReplacementSelectionSort<Capacity>::ConstructLoserTree(std::ifstream &fi) {
    for(int i=0;i!=Capacity;++i){
        workArea[i].key.first= workArea[i].key.second= workArea[i].mergeNum= loserTree[i]=0;//工作区,败者树初始化
    }
    for(int i=Capacity-1;i>=0;--i){//输入一个关键字
        fi >> workArea[i].key.first;
        fi >> workArea[i].key.second;
        workArea[i].mergeNum=1;//段号为1
        SelectMinMax(i);//调整败者树
    }//输入capacity个记录到工作区，并调整败者树
}

template<size_t Capacity>
void ReplacementSelectionSort<Capacity>::GetMergeSection(std::ifstream &fi, size_t &counts, int rc, int &rmax,
                                                         std::ofstream &fo) {
    while(workArea[loserTree[0]].mergeNum == rc){   //同属于一个段，不需要切换到下一个段
        int q=loserTree[0];                         //q是选出的minimax在工作区中的位置编号
        KeyType minimax=workArea[q].key;
        fo<<'\n';
        fo<<minimax.first<<' '<<minimax.second;		//将筛选出的一个数据记录输出
        ++counts;
        if(counts>=numOfData){
            workArea[q].mergeNum= rmax + 1;
            workArea[q].key.first= workArea[q].key.second=MAXIUM;
        }   //文件全部读取完之后，则只需要处理败者树中剩余未输出的元素
        //如果所有的数据记录都读取完，则没输出一个数据记录，就将该数据记录的段设置为虚段，表示结束，值设置为无限大
        else{
            fi >> workArea[q].key.first >> workArea[q].key.second;  //提取下一个数据记录
            if((workArea[q].key.first < minimax.first)||((workArea[q].key.first==minimax.first)&&(workArea[q].key.second<minimax.second))){              //如果小于上一个筛选出的数据记录，则它属于下一段
                rmax=rc+1;
                workArea[q].mergeNum=rmax;
            }
            else{
                workArea[q].mergeNum=rc;        //否则属于当前段
            }
        }
        SelectMinMax(q);    //调整败者树
    }
}

template<size_t Capacity>
ReplacementSelectionSort<Capacity>::ReplacementSelectionSort(size_t numOfData):numOfData(numOfData){}

template<size_t Capacity>
int ReplacementSelectionSort<Capacity>::nextSegNumber() {
    return workArea[loserTree[0]].mergeNum;
}


#endif //SEARCH101_REPLACEMENTSELECTIONSORT_H
