#ifndef _COMMAND_H
#define _COMMAND_H

#include <iostream>
#include <string>
#include <regex>

class Command
{
protected:
    enum COMMAND_TYPE commandType;
public:
    Command();
    Command(std::string&);
    void makeOfStr(std::string&);
    ~Command();
};

std::string trimStr(std::string&);

enum COMMAND_TYPE;

#endif