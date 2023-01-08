#include "CommandTree.h"

CommandTree::CommandTree()
{

}

void CommandTree::addCommand(std::string& str)
{
    str = trimStr(str);
    COMMAND_TYPE commandType = recognizeCommandType(str);
    Command newCommand;
    newCommand.commandType = commandType;
    commandList.push_back(newCommand);
}

COMMAND_TYPE CommandTree::recognizeCommandType(std::string& str)
{
    COMMAND_TYPE commandType = COMMAND_TYPE::UNDEFINED;
    std::cout << str << std::endl;
    /*
    TODO: unit tests
    check what we work with
    */

    //VAR_DEFINITION
    std::regex varDefinitionRegex("(\\w* \\w*=\\w*[;])");
    bool isVarDefinition = std::regex_search(str, varDefinitionRegex);
    isVarDefinition ? commandType = COMMAND_TYPE::VAR_DEFINITION : COMMAND_TYPE::UNDEFINED;

    std::regex varDeclarationRegex("(\\w* \\w*[;])");
    bool isVarDeclaration = std::regex_search(str, varDefinitionRegex);
    isVarDeclaration ? commandType = COMMAND_TYPE::VAR_DECLARATION : COMMAND_TYPE::UNDEFINED;

    //VAR_INITIALIZATION
    std::regex varInitializationRegex("(\\w*=\\w*[;])");
    bool isVarInitialization = std::regex_search(str, varInitializationRegex);
    isVarInitialization ? commandType = COMMAND_TYPE::VAR_INITIALIZATION : COMMAND_TYPE::UNDEFINED;


    //FUNC_DEFINITION
    std::regex funcDefinitionRegex("(\\w* \\w*[(]\\w*|\\s*[)])");
    bool isfuncDefinition = std::regex_search(str, funcDefinitionRegex);
    isfuncDefinition ? commandType = COMMAND_TYPE::FUNC_DEFINITION : COMMAND_TYPE::UNDEFINED;

    //FUNC_EXECUTION    
    std::regex funcExecuteRegex("(\\w*[(]\\w*[)][;])");
    bool isFuncExecute = std::regex_search(str, funcExecuteRegex);
    isFuncExecute ? commandType = COMMAND_TYPE::FUNC_EXECUTION : COMMAND_TYPE::UNDEFINED;


    std::cout << (int)commandType << std::endl;
    return commandType;
}

void CommandTree::displayCommandTree()
{
    std::cout << "\n\nCommandTree:" << std::endl;
    for (size_t i = 0; i < commandList.size(); i++)
    {
        std::cout << (int)commandList[i].commandType << std::endl;
    }
    
}

CommandTree::~CommandTree()
{

}

std::string trimStr(std::string& str)
{
    if (str.length() > 0)
    {
        //trim from front
        while (str[0] == ' ' || str[0] == '\t' || str[0] == '\n' || str[0] == '\0')
            str = str.substr(1, str.length());

        //trim from end
        while (str[0] == ' ' || str[0] == '\t' || str[0] == '\n' || str[0] == '\0')
            str = str.substr(0, str.length() - 1);
    }
    return str;
}