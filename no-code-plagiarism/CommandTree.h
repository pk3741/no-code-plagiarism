#ifndef _COMMAND_TREE_H
#define _COMMAND_TREE_H

#ifndef _NCP_CMDTREE_DEBUG_
#define _NCP_CMDTREE_DEBUG_ 0
#endif // !_NCP_CMDTREE_DEBUG_



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
    void addSubCommand(std::string&);
    std::string commandTypeIdToString(int);
    void displayCommandTree(std::string& prefix);
    COMMAND_TYPE createCommand(std::string&);
    std::vector<std::string> createParametersVec(std::string&);
    std::vector<std::shared_ptr<Command>>& getCommandListPtrVec();
    CommandTree * parent;
    void setParent(CommandTree*);
    std::string prefix;
    std::vector<std::vector<long>> comutations; //comutations
    virtual ~CommandTree();
};

std::string trimStr(std::string&);

#endif // !_COMMAND_TREE_H