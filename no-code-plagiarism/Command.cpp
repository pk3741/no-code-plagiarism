#include "Command.h"


Command::Command()
{

}

Command::Command(std::string& str)
{
    str = trimStr(str);
    makeOfStr(str);
}

void Command::makeOfStr(std::string& str)
{
    std::cout << str << std::endl;
}

Command::~Command()
{

}

std::string trimStr(std::string& str)
{
    //trim from front
    while(str[0]==' ' || str[0]=='\t' || str[0] == '\n' || str[0] == '\0')
        str = str.substr(1, str.length());

    //trim from end
    while (str[0] == ' ' || str[0] == '\t' || str[0] == '\n' || str[0] == '\0')
        str = str.substr(0, str.length()-1);
    
    return str;
}

enum COMMAND_TYPE
{
    //variable types
    VAR_DECLARATION = 0,
    VAR_DEFINITION = 1,
    VAR_INITIALIZATION = 2,
    VAR_ASSIGNMENT = 3
};