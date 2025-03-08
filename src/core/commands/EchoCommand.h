#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "Command.h"
#include <string>

using namespace std;

class EchoCommand : public Command{
    public:
    string execute(const RESPValue&  args) override;
};

#endif