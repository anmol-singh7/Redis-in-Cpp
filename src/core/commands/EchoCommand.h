#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "Command.h"
#include <string>

using namespace std;

class EchoCommand : public Command{
    public:
    bool validate(string& command, int ptr) override;
};

#endif