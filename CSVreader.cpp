//
// Created by AlexHoring on 2022/6/4.
//

#include "CSVreader.h"

CSVreader::CSVreader(const string &path) {
    fileIn.open(path, ios::in);
    state = READIN;
    isBufferFull = false;
}

char CSVreader::get_char() {
    char in;
    if (isBufferFull) {
        isBufferFull = false;
        in = readBuffer;
    } else {
        in = fileIn.get();
    }
    if (in == '\"') {
        readBuffer = fileIn.get();
        if (readBuffer != '\"') {
            if (readBuffer == '\x0d') {
                readBuffer = fileIn.get();
            }
            isBufferFull = true;
        }
    } else if (in == ',') {
        if (state == 2) {
            readBuffer = fileIn.get();
            if (readBuffer == '\x0d') {
                readBuffer = fileIn.get();
            }
            if (readBuffer == '\x0a') {
                in = '\x0a';
            } else {
                isBufferFull = true;
            }
        }
    }
    return in;
}

string CSVreader::get_sentense() {
    char in;
    string ret = "";
    state = READIN;
    do{
        in=get_char();
    }while(isblank(in));
    if (in == '\"' && (isBufferFull || readBuffer == '\x0a')) {
        state = BLOCK;
    } else if (in == ',') {
        state = READEND;
    } else {
        if (in != '\n') {
            ret += in;
        }
        state = LINE;
    }
    while (state != READEND) {
        if (end_of_file()) {
            state = READEND;
            ret = "";
        } else {
            in = get_char();
            if ((in == ','||in=='\x0a') && state == LINE) {
                state = READEND;
            } else if (in == '\"' &&
                       state == BLOCK &&
                       (isBufferFull && (readBuffer == ',' || readBuffer == '\x0a'))) {
                state = READEND;
                get_char();
            } else {
                ret += in;
            }
        }
    }
    return ret;
}

bool CSVreader::end_of_file() {
    return fileIn.eof();
}

