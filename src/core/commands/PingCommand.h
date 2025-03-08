#ifndef PINGCOMMAND_H
#define PINGCOMMAND_H

#include "Command.h"
#include <string>

using namespace std;

class PingCommand : public Command{
    public:
    string execute(const RESPValue& args) override;
};

#endif