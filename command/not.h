//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_NOT_H
#define BATCH_MANAGER_NOT_H

#include "basic/command.h"

struct Not : Command {
    void run() override {
        if (nextCommand != nullptr)
            next();
    }
};

#endif //BATCH_MANAGER_NOT_H
