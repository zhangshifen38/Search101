//
// Created by AlexHoring on 2022/6/13.
//

#include "PageEvaluate.h"

PageEvaluate::PageEvaluate(size_t newsID, size_t score, size_t category) :newsID(newsID),score(score),category(category){}

bool PageEvaluate::operator<(const PageEvaluate &p) const{
    if(this->category==p.category){
        return this->score<p.score;
    }else{
        return this->category<p.category;
    }
}
