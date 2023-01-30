#ifndef _COMMAND_TREE_H
#define _COMMAND_TREE_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include "Command.h"

class CommandTree
{
protected:
    std::vector<std::shared_ptr<Command>> commandList;
    std::vector<CommandVarDeclaration> cmdVarDecList;
    std::vector<CommandVarInitialization> cmdVarInitList;
    std::vector<CommandVarDefinition> cmdVarDefList;
    std::vector<CommandFuncDefinition> cmdFuncDefList;
    std::vector<CommandFuncExecution> cmdFuncExecList;
    std::vector<CommandFuncDeclaration> cmdFuncDecList;
    std::vector<std::tuple<std::string, int, std::string>> usedVarNames;
    std::vector<std::string> userFuncNames;
    int variable_counter;
public:
    CommandTree();
    void addCommand(std::string&);
    std::string commandTypeIdToString(int);
    void displayCommandTree();
    void createCommand(std::string&);
    std::vector<std::string> createParametersVec(std::string&);
    ~CommandTree();
};

std::string trimStr(std::string&);

#endif