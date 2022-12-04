#include "Command.h"


Command::Command()
{

}

Command::Command(std::string& str)
{
    makeOfStr(str);
}

void Command::makeOfStr(std::string& str)
{
    std::cout << str << std::endl;
}

Command::~Command()
{

}