//
// Created by AlexHoring on 2022/6/6.
//

#include "WordFilter.h"

bool WordFilter::end_of_sentence() {
    return index>=stream.size();
}

void WordFilter::set_sentence(std::string &&sentence) {
    this->stream=sentence;
    this->index=0;
    this->state=READY;
}

std::string WordFilter::get_word() {
    std::string result;
    while(state==READY){
        if(end_of_sentence()) {
            state = FILTED;
            result.clear();
        }else if(!std::isalpha(stream[index])&&!std::isdigit(stream[index])){
            ++index;
        }else{
            state=PICKING;
        }
    }
    while(state==PICKING){
        if(end_of_sentence()){
            state=FILTED;
        }else if(std::isalpha(stream[index])||stream[index]=='-'|| std::isdigit(stream[index])){
            result+= (char)tolower(stream[index]);
            ++index;
        }else{
            state=FILTED;
        }
    }
    state=READY;
    return result;
}
