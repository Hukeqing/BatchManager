//
// Created by keqing on 2020/10/9.
//

#ifndef BATCHMANAGER_CMD_H
#define BATCHMANAGER_CMD_H

#include "basic/command.h"

struct Cmd : Command {
    void run() override {
        string res, cmd, variable;

        commandIO >> cmd;
        res += cmd + ' ';

        while (commandIO >> variable) {
            environment::variableCheck(variable);
            res += variable + ' ';
        }

        res.pop_back();

        environment::addCmd(res, true);

        next();
    }
};

#endif //BATCHMANAGER_CMD_H
