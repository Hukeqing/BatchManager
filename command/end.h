//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_END_H
#define BATCH_MANAGER_END_H

#include "basic/command.h"

struct End : Command {
    Command *rollbackCommand;

    void run() override {
        if (rollbackCommand->rollback) rollbackCommand->rerun();
        else next();
    }
};

#endif //BATCH_MANAGER_END_H
