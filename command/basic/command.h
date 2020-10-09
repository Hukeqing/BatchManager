//
// Created by ke qing on 2020/10/8.
//

#ifndef BATCH_MANAGER_COMMAND_H
#define BATCH_MANAGER_COMMAND_H

#include "environment.h"

struct Command {
    Command *nextCommand;
    string commands;
    stringstream commandIO;
    bool rollback;

    Command() : nextCommand(nullptr), rollback(false) {}

    void next() const {
        nextCommand->commandIO.clear();
        nextCommand->commandIO << nextCommand->commands;
        nextCommand->run();
    }

    virtual void run() = 0;

    virtual void rerun() {};
};

#endif //BATCH_MANAGER_COMMAND_H
