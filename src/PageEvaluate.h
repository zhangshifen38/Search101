//
// Created by AlexHoring on 2022/6/13.
//

#ifndef SEARCH101_PAGEEVALUATE_H
#define SEARCH101_PAGEEVALUATE_H


#include <cstddef>

class PageEvaluate {
public:
    PageEvaluate()=default;
    PageEvaluate(size_t newsID,size_t score,size_t category);
    bool operator<(const PageEvaluate &p) const;

    size_t newsID;
    size_t score;
    size_t category;

};


#endif //SEARCH101_PAGEEVALUATE_H
