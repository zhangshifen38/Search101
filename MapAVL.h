//
// Created by AlexHoring on 2022/6/9.
//

#ifndef SEARCH101_MAPAVL_H
#define SEARCH101_MAPAVL_H

#include <functional>
#include <utility>
#include "AVLtree.h"

template<typename KeyType, typename ValueType, typename Compare=std::less<KeyType> >
class MapCompare {
public:
    bool operator()(const std::pair<KeyType, ValueType> &a, const std::pair<KeyType, ValueType> &b) {
        Compare compare = Compare();
        return compare(a.first, b.first);
    }
};


template<typename KeyType, typename ValueType, typename Compare=std::less<KeyType> >
class MapAVL : protected AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> > {
public:
    using iterator=typename AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::iterator;
    using MapNodeType=typename AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::AVLnodeType;
    using ElementType=std::pair<KeyType, ValueType>;
    MapAVL()=default;
    iterator begin();
    iterator end();
    void insert(ElementType data);
    void clear();
    bool empty();
    iterator find(KeyType key);
    void erase(iterator deleteLocale);
    void swap(MapAVL<KeyType,ValueType,Compare> &mapAVL);
    ValueType& operator[](KeyType key);
};

template<typename KeyType, typename ValueType, typename Compare>
typename MapAVL<KeyType, ValueType, Compare>::iterator MapAVL<KeyType, ValueType, Compare>::begin() {
    return AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::begin();
}

template<typename KeyType, typename ValueType, typename Compare>
typename MapAVL<KeyType, ValueType, Compare>::iterator MapAVL<KeyType, ValueType, Compare>::end() {
    return AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::end();
}

template<typename KeyType, typename ValueType, typename Compare>
void MapAVL<KeyType, ValueType, Compare>::insert(MapAVL::ElementType data) {
    AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::insert(data);
}

template<typename KeyType, typename ValueType, typename Compare>
void MapAVL<KeyType, ValueType, Compare>::clear() {
    AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::clear();
}

template<typename KeyType, typename ValueType, typename Compare>
bool MapAVL<KeyType, ValueType, Compare>::empty() {
    return this->nodeNumber==0;
}

template<typename KeyType, typename ValueType, typename Compare>
typename MapAVL<KeyType, ValueType, Compare>::iterator MapAVL<KeyType, ValueType, Compare>::find(KeyType key) {
    return AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::find(MapAVL::ElementType(key,ValueType()));
}

template<typename KeyType, typename ValueType, typename Compare>
void MapAVL<KeyType, ValueType, Compare>::erase(MapAVL::iterator deleteLocale) {
    AVLtree<std::pair<KeyType, ValueType>, MapCompare<KeyType, ValueType, Compare> >::erase(deleteLocale);
}

template<typename KeyType, typename ValueType, typename Compare>
void MapAVL<KeyType, ValueType, Compare>::swap(MapAVL<KeyType, ValueType, Compare> &mapAVL) {
    MapAVL::MapNodeType temp=this->root;
    this->root=mapAVL.root;
    mapAVL.root=temp;
}

template<typename KeyType, typename ValueType, typename Compare>
ValueType &MapAVL<KeyType, ValueType, Compare>::operator[](KeyType key) {
    iterator tryToFind=find(key);
    if(tryToFind==end()){
        insert(ElementType(key,ValueType()));
        tryToFind= find(key);
    }
    return (*tryToFind).second;
}


#endif //SEARCH101_MAPAVL_H
