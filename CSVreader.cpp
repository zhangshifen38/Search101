//
// Created by AlexHoring on 2022/6/4.
//

#include "CSVreader.h"

CSVreader::CSVreader(string &&path) {
    fileIn.open(path, ios::in);
    state = 0;
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
            if (readBuffer != '\x0a') {
                isBufferFull = true;
            }
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
    state = 0;
    in = get_char();
    if (in == '\"' && (isBufferFull || readBuffer == '\x0a')) {
        state = 2;
    } else if (in == ',') {
        state = 3;
    } else {
        ret += in;
        state = 1;
    }
    while (state != 3) {
        if (end_of_file()) {
            state = 3;
            ret = "";
        } else {
            in = get_char();
            if (in == ',' && state == 1) {
                state = 3;
            } else if (in == '\"' && state == 2 && isBufferFull && readBuffer == ',') {
                state = 3;
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

