//
// Created by AlexHoring on 2022/6/9.
//

#ifndef SEARCH101_SETAVL_H
#define SEARCH101_SETAVL_H

#include "AVLtree.h"

template<typename Type,typename Compare=std::less<Type> >
class SetAVL: protected AVLtree<Type,Compare>{
public:
    using iterator = typename AVLtree<Type, Compare>::iterator;
    using setNodeType = typename AVLtree<Type,Compare>::AVLnodeType;
    SetAVL()=default;
    iterator begin();
    iterator end();
    void insert(Type data);
    void clear();
    size_t size();
    bool empty();
    iterator find(Type toSearch);
    void erase(iterator deleteLocale);
    void swap(SetAVL<Type,Compare> &setAVL);
};

template<typename Type,typename Compare>
typename SetAVL<Type,Compare>::iterator SetAVL<Type, Compare>::begin() {
    return AVLtree<Type,Compare>::begin();
}

template<typename Type,typename Compare>
typename SetAVL<Type,Compare>::iterator SetAVL<Type, Compare>::end() {
    return AVLtree<Type,Compare>::end();
}

template<typename Type, typename Compare>
void SetAVL<Type, Compare>::insert(Type data) {
    AVLtree<Type,Compare>::insert(data);
}

template<typename Type, typename Compare>
void SetAVL<Type, Compare>::clear() {
    AVLtree<Type,Compare>::clear();
}

template<typename Type, typename Compare>
bool SetAVL<Type, Compare>::empty() {
    return this->nodeNumber ==0;
}

template<typename Type, typename Compare>
size_t SetAVL<Type, Compare>::size() {
    return this->nodeNumber;
}

template<typename Type, typename Compare>
typename SetAVL<Type,Compare>::iterator SetAVL<Type, Compare>::find(Type toSearch) {
    return AVLtree<Type,Compare>::find(toSearch);
}

template<typename Type, typename Compare>
void SetAVL<Type, Compare>::erase(SetAVL::iterator deleteLocale) {
    AVLtree<Type,Compare>::erase(deleteLocale);
}

template<typename Type, typename Compare>
void SetAVL<Type, Compare>::swap(SetAVL<Type, Compare> &setAVL) {
    setNodeType temp=this->root;
    this->root=setAVL.root;
    setAVL.root=temp;
}



#endif //SEARCH101_SETAVL_H
