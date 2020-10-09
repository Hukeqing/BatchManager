//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_RUN_H
#define BATCH_MANAGER_RUN_H

#include "basic/command.h"

struct Run : Command {
    void run() override {
        string res, cmd, variable;

        commandIO >> cmd;
        res = cmd + ' ';

        while (commandIO >> variable) {
            environment::variableCheck(variable);
            res += variable + ' ';
        }

        res.pop_back();

        environment::addCmd(res, false);

        next();
    }
};

#endif //BATCH_MANAGER_RUN_H
