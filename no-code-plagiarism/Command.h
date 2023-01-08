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
    FUNC_EXECUTION = 5
};

class Command
{
public:
    COMMAND_TYPE commandType;
    Command();
    Command(std::string&);
    void makeOfStr(std::string&);
    ~Command();
};


#endif