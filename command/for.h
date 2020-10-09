//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_FOR_H
#define BATCH_MANAGER_FOR_H

#include "basic/command.h"

struct For : Command {
    int pos;
    vector<string> *forValue;
    string target;

    void run() override {
        string variable;
        commandIO >> variable >> target;

        pos = 0;
        forValue = &environment::getVariableVector(variable);
        if (pos < forValue->size())
            environment::setVariable(target, forValue->at(pos));
        if (pos + 1 >= forValue->size()) rollback = false;
        else rollback = true;

        next();
    }

    void rerun() override {
        pos++;
        if (pos < forValue->size())
            environment::setVariable(target, forValue->at(pos));
        if (pos + 1 >= forValue->size()) rollback = false;
        else rollback = true;

        next();
    }
};

#endif //BATCH_MANAGER_FOR_H
