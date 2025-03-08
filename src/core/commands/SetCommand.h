#ifndef SETCOMMAND_H
#define SETCOMMAND_H

#include "Command.h"
#include "../storage/Database.h"

class SetCommand : public Command {
public:
    string execute(const RESPValue& args) override;
};
#endif