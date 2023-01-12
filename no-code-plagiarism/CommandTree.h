#ifndef _COMMAND_TREE_H
#define _COMMAND_TREE_H

#include <vector>
#include <iostream>
#include <string>
#include "Command.h"

class CommandTree
{
protected:
    std::vector<Command*> commandList;
    std::vector<CommandVarDeclaration> cmdVarDecList;
public:
    CommandTree();
    void addCommand(std::string&);
    void displayCommandTree();
    void createCommand(std::string&);
    ~CommandTree();
};

std::string trimStr(std::string&);

#endif