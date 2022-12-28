#include "Command.h"

enum COMMAND_TYPE
{
    //variable types
    UNDEFINED = 0,
    VAR_DECLARATION = 1,
    VAR_INITIALIZATION = 2,
    VAR_DEFINITION = 3
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

    //VAR_DEFINITION
    std::regex varDefinitionRegex("(\\w* \\w*=\\w*)");
    bool isVarDefinition = std::regex_search(str, varDefinitionRegex);
    
    if (isVarDefinition)
    {
        commandType = COMMAND_TYPE::VAR_DEFINITION;
    }
    else
    { 
        //VAR_DECLARATION
        std::regex varDeclarationRegex("(\\w* \\w*)");
        bool isVarDeclaration = std::regex_search(str, varDefinitionRegex);
        isVarDeclaration ? commandType = COMMAND_TYPE::VAR_DECLARATION : NULL;

        //VAR_INITIALIZATION
        std::regex varInitializationRegex("(\\w*=\\w*)");
        bool isVarInitialization = std::regex_search(str, varInitializationRegex);
        isVarInitialization ? commandType = COMMAND_TYPE::VAR_INITIALIZATION : NULL;
    }
    std::cout << commandType << std::endl;
    



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

