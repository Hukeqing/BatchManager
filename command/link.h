//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_LINK_H
#define BATCH_MANAGER_LINK_H

#include "basic/command.h"

struct Link : Command {
    void run() override {
        string target, by, res, variable;
        commandIO >> target >> by;

        environment::variableCheck(by);

        while (commandIO >> variable) {
            environment::variableCheck(variable);
            res += variable + by;
        }

        for (int i = 0; i < by.size(); ++i) res.pop_back();


        environment::setVariable(target, move(res));

        next();
    }
};

#endif //BATCH_MANAGER_LINK_H
