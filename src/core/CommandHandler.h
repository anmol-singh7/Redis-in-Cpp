#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
using namespace std;

class CommandHandler{

    public:
    virtual string handleCommand(char *cmd, int sz_Command);
};

#endif