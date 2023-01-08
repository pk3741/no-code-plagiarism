#ifndef _COMMAND_TREE_H
#define _COMMAND_TREE_H

#include <vector>
#include <iostream>
#include <string>
#include "Command.h"

class CommandTree
{
protected:
    std::vector<Command> commandList;
public:
    CommandTree();
    void addCommand(std::string&);
    void displayCommandTree();
    COMMAND_TYPE recognizeCommandType(std::string&);
    ~CommandTree();
};

std::string trimStr(std::string&);

#endif