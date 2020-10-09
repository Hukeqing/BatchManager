//
// Created by ke qing on 2020/10/8.
//

#ifndef BATCH_MANAGER_ENVIRONMENT_H
#define BATCH_MANAGER_ENVIRONMENT_H

#include "../../common/exception.h"

struct CmdLine {
    string cmd, in, out, err;
    bool systemCmd;

    string get() const {
        string res = cmd;
        if (!in.empty()) res += " < " + in;
        if (!out.empty()) res += " 1>> " + out;
        if (!err.empty()) res += " 2>> " + err;
        return res;
    }
};

namespace environment {
    string inputFile;
    string outputFile;
    string errorFile;
    string logFile;
    int freshTime = 300;
    double maxMember = 0.5;
    long long maxRunTime = 172800;
    int maxProcessNum = 1;

    vector<CmdLine> commandList;
    // NOLINTNEXTLINE
    unordered_map<string, vector<string>> variable({{"NULL", {""}}});

    string &getVariable(const string &name) {
        auto iter = variable.find(name);
        if (iter == variable.end()) throw Unknown("Variable", name);
        return iter->second[0];
    }

    vector<string> &getVariableVector(const string &name) {
        auto iter = variable.find(name);
        if (iter == variable.end()) throw Unknown("Variable", name);
        return iter->second;
    }

    void setVariable(const string &target, const string &res) {
        auto iter = environment::variable.find(target);
        if (iter == environment::variable.end()) iter = environment::variable.insert({target, {}}).first;

        iter->second.clear();
        iter->second.push_back(res);
    }

    void setVariable(const string &target, string &&res) {
        auto iter = environment::variable.find(target);
        if (iter == environment::variable.end()) iter = environment::variable.insert({target, {}}).first;

        iter->second.clear();
        iter->second.push_back(move(res));
    }

    void setVariable(const string &target, vector<string> &&res) {
        auto iter = environment::variable.find(target);
        if (iter == environment::variable.end()) iter = environment::variable.insert({target, {}}).first;

        iter->second.clear();
        iter->second = move(res);
    }

    void variableCheck(string &str) {
        if (str.back() == '#') {
            str.pop_back();
            str = getVariable(str);
        }
    }

    void addCmd(string &str, bool sys) {
        commandList.push_back({str, inputFile, outputFile, errorFile, sys});
    }

    // NOLINTNEXTLINE
    unordered_map<string, function<void(stringstream &)>> envFunc(
            {
                    {"input",         [](stringstream &ss) {
                        ss >> inputFile;
                        variableCheck(inputFile);
                    }},
                    {"output",        [](stringstream &ss) {
                        ss >> outputFile;
                        variableCheck(outputFile);
                    }},
                    {"error",         [](stringstream &ss) {
                        ss >> errorFile;
                        variableCheck(errorFile);
                    }},
                    {"log",           [](stringstream &ss) {
                        ss >> logFile;
                        variableCheck(logFile);
                    }},
                    {"fresh",         [](stringstream &ss) {
                        ss >> freshTime;
                    }},
                    {"maxMember",     [](stringstream &ss) {
                        ss >> maxMember;
                    }},
                    {"maxRunTime",    [](stringstream &ss) {
                        ss >> maxRunTime;
                    }},
                    {"maxProcessNum", [](stringstream &ss) {
                        ss >> maxProcessNum;
                    }}
            });

}

#endif //BATCH_MANAGER_ENVIRONMENT_H
