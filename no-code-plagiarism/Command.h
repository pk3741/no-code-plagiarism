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
    ~Command();
};

//VAR_DECLARATION 1
class CommandVarDeclaration : public Command
{
public:
    
    CommandVarDeclaration();
    ~CommandVarDeclaration();
};

//VAR_INITIALIZATION 2
class CommandVarInitialization : public Command
{
public:
    CommandVarInitialization();
    ~CommandVarInitialization();
};

//VAR_DEFINITION 3
class CommandVarDefinition : public Command
{
public:
    CommandVarDefinition();
    ~CommandVarDefinition();
};


//FUNC_DEFINITION 4
class CommandFuncDefinition : public Command
{
public:
    CommandFuncDefinition();
    ~CommandFuncDefinition();
};

//FUNC_EXECUTION  5
class CommandFuncExecution : public Command
{
public:
    CommandFuncExecution();
    ~CommandFuncExecution();
};

//FUNC_DECLARATION 6
class CommandFuncDeclaration : public Command
{
public:
    CommandFuncDeclaration();
    ~CommandFuncDeclaration();
};

#endif