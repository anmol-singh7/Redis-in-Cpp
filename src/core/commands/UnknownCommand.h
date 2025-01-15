#ifndef UnknownCOMMAND_H
#define UnknownCOMMAND_H

#include "Command.h"
#include <string>

using namespace std;

class UnknownCommand : public Command{
    public:
    bool validate(string& command, int ptr) override;
};

#endif