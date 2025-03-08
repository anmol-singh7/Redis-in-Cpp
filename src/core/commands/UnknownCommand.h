#ifndef UnknownCOMMAND_H
#define UnknownCOMMAND_H

#include "Command.h"
#include <string>

using namespace std;

class UnknownCommand : public Command{
    public:
    string execute(const RESPValue& args) override;
};

#endif