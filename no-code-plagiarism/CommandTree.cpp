#include "CommandTree.h"

CommandTree::CommandTree()
{

}

void CommandTree::addCommand(std::string& str)
{
    str = trimStr(str);
    Command newCommand = createCommand(str);
    commandList.push_back(newCommand);
}

Command CommandTree::createCommand(std::string& str)
{
    Command * newCommand = new Command();
    COMMAND_TYPE commandType = COMMAND_TYPE::UNDEFINED;
    std::cout << "Line: " << str << std::endl;
    /*
    TODO: unit tests
    check what we work with
    */

    std::smatch matches;
    bool found = false;
    //VAR_DECLARATION 1
    if(found==false)
    { 
        std::regex varDeclarationRegex("(\\w+)\\s(\\w+)[;]");
        bool isVarDeclaration = std::regex_match(str, matches, varDeclarationRegex);
        isVarDeclaration ? commandType = COMMAND_TYPE::VAR_DECLARATION : COMMAND_TYPE::UNDEFINED;
        isVarDeclaration ? found = true : found = false;
        newCommand = new CommandVarDeclaration();
    }

    //VAR_INITIALIZATION 2
    if(found==false)
    { 
        std::regex varInitializationRegex("(\\w+)=(\\w+)[;]");
        bool isVarInitialization = std::regex_match(str, matches, varInitializationRegex);
        isVarInitialization ? commandType = COMMAND_TYPE::VAR_INITIALIZATION : COMMAND_TYPE::UNDEFINED;
        isVarInitialization ? found = true : found = false;
        newCommand = new CommandVarInitialization();
    }

    //VAR_DEFINITION 3
    if (found == false)
    {
        std::regex varDefinitionRegex("(\\w+)(\\s)(\\w+)=(\\w+)[;]");
        bool isVarDefinition = std::regex_match(str, matches, varDefinitionRegex);
        isVarDefinition ? commandType = COMMAND_TYPE::VAR_DEFINITION : COMMAND_TYPE::UNDEFINED;
        isVarDefinition ? found = true : found = false;
        newCommand = new CommandVarDefinition();
    }

    //FUNC_DEFINITION 4
    if (found == false)
    {
        std::regex funcDefinitionRegex("(\\w+)(\\s)(\\w+)([(])(.*)([)])");
        bool isfuncDefinition = std::regex_match(str, matches, funcDefinitionRegex);
        isfuncDefinition ? commandType = COMMAND_TYPE::FUNC_DEFINITION : COMMAND_TYPE::UNDEFINED;
        isfuncDefinition ? found = true : found = false;
        newCommand = new CommandFuncDefinition();
    }

    //FUNC_EXECUTION  5
    if (found == false)
    {
        std::regex funcExecuteRegex("(\\w+)([(])(.*)([)])([;])");
        bool isFuncExecute = std::regex_match(str, matches, funcExecuteRegex);
        isFuncExecute ? commandType = COMMAND_TYPE::FUNC_EXECUTION : COMMAND_TYPE::UNDEFINED;
        isFuncExecute ? found = true : found = false;
        newCommand = new CommandFuncExecution();
    }

    //FUNC_DECLARATION 6
    if (found == false)
    {
        std::regex funcDeclarationRegex("(\\w+)(\\s)(\\w+)([(])(.*)([)])([;])");
        bool isFuncDeclaration = std::regex_match(str, matches, funcDeclarationRegex);
        isFuncDeclaration ? commandType = COMMAND_TYPE::FUNC_DECLARATION : COMMAND_TYPE::UNDEFINED;
        isFuncDeclaration ? found = true : found = false;
        newCommand = new CommandFuncDeclaration();
    }
    newCommand->commandType = commandType;

    std::cout << (int)commandType << std::endl;
    std::cout << "Matches(" << matches.size() << "):" << std::endl;
    for (size_t i = 0; i < matches.size(); i++)
    {
        std::ssub_match sub_match = matches[i];
        std::string ssub_match = sub_match.str();
        std::cout << "Match " << i << ": " << ssub_match << std::endl;
    }
    std::cout << "\n";  

    return *newCommand;
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