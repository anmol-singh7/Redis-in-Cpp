#ifndef GETCOMMAND_H
#define GETCOMMAND_H

#include "Command.h"

class GetCommand : public Command{
    private:
    Database *db;
    
    public:    
    string execute(const RESPValue&  args) override;
};

#endif