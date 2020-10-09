//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_JOIN_H
#define BATCH_MANAGER_JOIN_H

#include "basic/command.h"

struct Join : Command {
    void run() override {
        string target, variable;
        vector<string> res;

        commandIO >> target;

        while (commandIO >> variable) {
            if (variable.back() == '#') {
                variable.pop_back();
                vector<string> &tmp = environment::getVariableVector(variable);
                for (const auto &item : tmp) res.push_back(item);
            } else
                res.push_back(variable);
        }

        environment::setVariable(target, move(res));
        next();
    }
};

#endif //BATCH_MANAGER_JOIN_H
