//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_SET_H
#define BATCH_MANAGER_SET_H

#include "basic/command.h"

struct Set : Command {
    void run() override {
        string setValue;
        commandIO >> setValue;

        auto iter = environment::envFunc.find(setValue);
        if (iter == environment::envFunc.end()) throw Unknown("setting variable", setValue);
        else iter->second(commandIO);

        next();
    }
};

#endif //BATCH_MANAGER_SET_H
