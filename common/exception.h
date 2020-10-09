//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_EXCEPTION_H
#define BATCH_MANAGER_EXCEPTION_H

#include <bits/stdc++.h>

using namespace std;

struct Unknown : public exception {
    string unknown;

    explicit Unknown(const string &type, const string &cmd) : unknown("Unknown " + type + ": " + cmd) {}

    const char *what() const noexcept override {
        return unknown.data();
    }
};

#endif //BATCH_MANAGER_EXCEPTION_H
