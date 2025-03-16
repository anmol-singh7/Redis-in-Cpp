#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
using namespace std;

class CommandHandler{

    public:
    static string handleCommand(char *cmd, int sz_Command);
};

#endif