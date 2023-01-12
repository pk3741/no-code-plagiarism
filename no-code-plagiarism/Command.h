#ifndef _COMMAND_H
#define _COMMAND_H

#include <iostream>
#include <string>
#include <regex>

enum class COMMAND_TYPE
{
    //variable types
    UNDEFINED = 0,
    VAR_DECLARATION = 1,
    VAR_INITIALIZATION = 2,
    VAR_DEFINITION = 3,
    FUNC_DEFINITION = 4,
    FUNC_EXECUTION = 5,
    FUNC_DECLARATION = 6
};

//INITIAL CLASS
class Command
{
public:
    COMMAND_TYPE commandType;
    Command();
    virtual ~Command();
};

//VAR_DECLARATION 1
class CommandVarDeclaration : public Command
{
public:
    int varDeclarationId;
    std::string varType;
    CommandVarDeclaration();
    virtual ~CommandVarDeclaration();
};

//VAR_INITIALIZATION 2
class CommandVarInitialization : public Command
{
public:
    int varDeclarationId;
    std::string varData;
    CommandVarInitialization();
    virtual ~CommandVarInitialization();
};

//VAR_DEFINITION 3
class CommandVarDefinition : public Command
{
public:
    int varDeclarationId;
    std::string varType;
    std::string varData;
    CommandVarDefinition();
    virtual ~CommandVarDefinition();
};


//FUNC_DEFINITION 4
class CommandFuncDefinition : public Command
{
public:
    int funcDeclarationId;
    std::string returnType;
    std::vector<std::string> parameters;
    std::vector<Command> subCommands;
    CommandFuncDefinition();
    virtual ~CommandFuncDefinition();
};

//FUNC_EXECUTION  5
class CommandFuncExecution : public Command
{
public:
    int funcDeclarationId;
    std::vector<std::string> parameters;
    CommandFuncExecution();
    virtual ~CommandFuncExecution();
};

//FUNC_DECLARATION 6
class CommandFuncDeclaration : public Command
{
public:
    int funcDeclarationId;
    std::string returnType;
    std::vector<std::string> parameters;
    CommandFuncDeclaration();
    virtual ~CommandFuncDeclaration();
};

#endif