#ifndef _COMMAND_TREE_H
#define _COMMAND_TREE_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include "Command.h"

class Command;

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

    std::vector<CommandStatementFor> cmdStmtForList;
    std::vector<CommandStatementWhile> cmdStmtWhileList;
    std::vector<CommandStatementIf> cmdStmtIfList;

    std::vector<std::tuple<std::string, int, std::string>> usedVarNames;
    std::vector<std::string> userFuncNames;
    int variable_counter;
public:
    CommandTree();
    COMMAND_TYPE addCommand(std::string&);
    std::string commandTypeIdToString(int);
    void displayCommandTree();
    COMMAND_TYPE createCommand(std::string&);
    std::vector<std::string> createParametersVec(std::string&);
    std::vector<std::shared_ptr<Command>>& getCommandListPtrVec();
    ~CommandTree();
};

std::string trimStr(std::string&);

#endif