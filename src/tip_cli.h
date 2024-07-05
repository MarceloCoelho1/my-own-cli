#ifndef TIP_CLI_H
#define TIP_CLI_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ANSI escape codes for color
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string GREEN = "\033[32m";
const string CYAN = "\033[36m";
const string YELLOW = "\033[33m";

struct CommandDefinition {
    string description;
    string command;
    vector<string> args;
};

int help();
int ts_backend_boilerplate();

#endif // TIP_CLI_H
