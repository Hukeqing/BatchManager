//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_VAR_H
#define BATCH_MANAGER_VAR_H

#include "basic/command.h"

struct Var : Command {
    void run() override {
        string variableType, variableName, variableValue;
        commandIO >> variableType >> variableName;

        auto iter = environment::variable.find(variableName);
        if (iter == environment::variable.end()) iter = environment::variable.insert({variableName, {}}).first;
        else iter->second.clear();

        if (variableType == "str") {
            while (commandIO.peek() == ' ') commandIO.get();
            getline(commandIO, variableValue);
            iter->second.push_back(move(variableValue));
        } else if (variableType == "vector") {
            while (commandIO >> variableValue)
                iter->second.push_back(move(variableValue));
        } else {
            throw Unknown("variable type", variableType);
        }

        next();
    }
};

#endif //BATCH_MANAGER_VAR_H
