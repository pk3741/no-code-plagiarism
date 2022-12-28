#include "Command.h"

enum COMMAND_TYPE
{
    //variable types
    VAR_DECLARATION = 0,
    VAR_INITIALIZATION = 1,
    VAR_DEFINITION = 2  
};

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
    /*
    TODO: unit tests
    check what we work with
    */

    //VAR_DECLARATION
    std::regex varDeclarationRegex("(\\w* \\w*)");
    std::cout << "DECLARATION: " << std::regex_search(str, varDeclarationRegex) << std::endl;
    commandType = VAR_DECLARATION;

    //VAR_INITIALIZATION
    std::regex varInitializationRegex("(\\w*=\\w*)");
    std::cout << "INITIALIZATION: " << std::regex_search(str, varInitializationRegex) << std::endl;
    commandType = VAR_INITIALIZATION;

    //VAR_DEFINITION
    std::regex varDefinitionRegex("(\\w* \\w*=\\w*)");
    std::cout << "DEFINITION: " << std::regex_search(str, varDefinitionRegex) << std::endl;
    commandType=VAR_DEFINITION;



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

