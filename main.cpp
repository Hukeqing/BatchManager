#include "command/__init__.h"
#include "batch/process.h"
#include <unistd.h>

int cmdPtr;

void translate(ifstream &bm) {
    Command *root, *cur;
    string cmdLine, cmd;
    stack<Command *> rollback;

    root = (Command *) new Not();
    cur = root;
    while (getline(bm, cmdLine)) {
        stringstream ss(cmdLine);
        ss >> cmd;
        Command *newCmd;

        if (cmd == "cmd")
            newCmd = (Command *) new Cmd();
        else if (cmd == "end") {
            auto newEnd = new End();
            if (rollback.empty()) throw logic_error("Can`t found the 'begin' for 'end'");
            newEnd->rollbackCommand = rollback.top();
            rollback.pop();
            newCmd = newEnd;
        } else if (cmd == "for") {
            newCmd = (Command *) new For();
            rollback.push(newCmd);
        } else if (cmd == "join")
            newCmd = (Command *) new Join();
        else if (cmd == "link")
            newCmd = (Command *) new Link();
        else if (cmd == "not")
            newCmd = (Command *) new Not();
        else if (cmd == "run")
            newCmd = (Command *) new Run();
        else if (cmd == "set")
            newCmd = (Command *) new Set();
        else if (cmd == "var")
            newCmd = (Command *) new Var();

        cur->nextCommand = newCmd;
        while (ss.peek() == ' ') ss.get();
        getline(ss, newCmd->commands);
        cur = newCmd;
    }

    auto newCmd = (Command *) new Not();
    cur->nextCommand = newCmd;

    if (!rollback.empty()) throw logic_error("Can`t found the 'end' for 'begin'");

    root->run();
}

#ifndef WINDOWS

void newProcess(const CmdLine &cmd) {
    Process newProcess;
    newProcess.startTime = time(nullptr);
    newProcess.maxMember = 0;
    newProcess.cmd = cmd.cmd;
    newProcess.pid = fork();
    if (newProcess.pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd.get().data(), (char *) nullptr);
        exit(0);
    } else {
        string tmp =
                "ps -aux | grep \"" + newProcess.cmd + R"(" | grep -v grep | grep -v "sh -c" 1> fresh_check_process)";
        system(tmp.data());
        ifstream psLog("fresh_check_process");
        psLog >> tmp >> newProcess.pid;
        process.insert({newProcess.pid, newProcess});
    }
}

void removeProcess(int pid, int type) {
    auto curProcess = process[pid];
    cout << "Process Over: " << curProcess.cmd << endl;
    cout << "Cost time: " << time(nullptr) - curProcess.startTime << 's' << endl;
    cout << "Max member cost: " << curProcess.maxMember << "%" << endl;
    string result;
    switch (type) {
        case 0:
            result = "Kill by System, maybe OK?";
            break;
        case 1:
            result = "Time Limit Exceeded";
            break;
        case 2:
            result = "Memory Limit Exceeded";
            break;
        default:
            result = "Unknown Result";
            break;
    }
    cout << result << endl;
    cout << endl;
    system(("kill " + to_string(pid) + " 2>&1 >/dev/null").data());
    process.erase(pid);
}

void check() {
    vector<pair<int, int>> erasePid;
    for (auto &item : process) {
        string cmd =
                "ps -aux | grep \" " + to_string(item.first) + R"( " | grep -v grep | grep -v "sh -c" 1> fresh_check_process)";
        system(cmd.data());
        ifstream psLog("fresh_check_process");
        for (int i = 0; i < 3; ++i) psLog >> cmd;

        if (!psLog) {
            erasePid.emplace_back(item.first, 0);
            continue;
        }

        double curMember;
        psLog >> curMember;
        item.second.maxMember = max(curMember, item.second.maxMember);
        bool flag = false;
        while (psLog >> cmd) {
            if (cmd == "<defunct>") {
                erasePid.emplace_back(item.first, 0);
                flag = true;
                break;
            }
        }
        if (!flag) {
            long long runTime = time(nullptr) - item.second.startTime;
            if (runTime > environment::maxRunTime)
                erasePid.emplace_back(item.first, 1);
            else if (item.second.maxMember > environment::maxMember)
                erasePid.emplace_back(item.first, 2);
        }
    }
    for (auto &item : erasePid) removeProcess(item.first, item.second);
    while (process.size() < environment::maxProcessNum && cmdPtr < environment::commandList.size()) {
        auto cmd = environment::commandList[cmdPtr].get();
        cout << "Run Command: " << cmd << endl;
        if (environment::commandList[cmdPtr].systemCmd) system(cmd.data());
        else newProcess(environment::commandList[cmdPtr]);
        cmdPtr++;
    }
    auto tt = time(nullptr);
    tm *t = localtime(&tt);
    cout << t->tm_year + 1900 << '-' << t->tm_mon + 1 << '-' << t->tm_mday << ' ' << t->tm_hour << ':' << t->tm_min
         << ':' << t->tm_sec << endl;
    cout << "Check over" << endl << endl;
}

#endif

int main(int argc, char **argv) {
#ifdef DEBUG
    ifstream bm("in.txt");
#else
    ifstream bm(argv[1]);
#endif
    translate(bm);
#ifndef WINDOWS
    if (!environment::logFile.empty())
        freopen(environment::logFile.data(), "w", stdout);

    environment::variable.clear();
    while (cmdPtr < environment::commandList.size() || !process.empty()) {
        check();
        this_thread::sleep_for(chrono::seconds(environment::freshTime));
    }
#endif
}
