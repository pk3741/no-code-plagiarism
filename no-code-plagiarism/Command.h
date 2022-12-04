#ifndef _COMMAND_H
#define _COMMAND_H

#include <iostream>
#include <string>

class Command
{
public:
    Command();
    Command(std::string&);
    void makeOfStr(std::string&);
    ~Command();
};

#endif