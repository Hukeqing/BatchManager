//
// Created by keqing on 2020/10/8.
//

#ifndef BATCH_MANAGER_PROCESS_H
#define BATCH_MANAGER_PROCESS_H

#include "../common/exception.h"

struct Process {
    int pid;
    long long startTime;
    double maxMember;
    string cmd;
};

map<int, Process> process;

#endif //BATCH_MANAGER_PROCESS_H
