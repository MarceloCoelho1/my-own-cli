#ifndef TIP_CLI_H
#define TIP_CLI_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ANSI escape codes for color
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string GREEN = "\033[32m";
const string CYAN = "\033[36m";
const string YELLOW = "\033[33m";
const string RED = "\033[38;2;255;99;71m";  
const string PURPLE = "\033[38;2;204;153;255m";
const string LIGHT_YELLOW = "\033[38;2;255;255;128m";   


struct CommandDefinition {
    string description;
    string command;
    vector<string> args;
};

struct Directory {
    string directory;
    vector<string> files;
};


int help();
int ts_backend_boilerplate();
int ts_react_frontend_boilerplate();
int osfetch(); 
#endif // TIP_CLI_H
