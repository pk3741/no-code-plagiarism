#include "CommandTree.h"

CommandTree::CommandTree()
{

}

void CommandTree::addCommand(std::string& str)
{
    str = trimStr(str);
    createCommand(str);
}

void CommandTree::createCommand(std::string& str)
{
    COMMAND_TYPE commandType = COMMAND_TYPE::UNDEFINED;
    std::cout << "Line: " << str << std::endl;
    /*
*   COMMAND TYPE RECOGNITION
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
    }

    //VAR_INITIALIZATION 2
    if(found==false)
    { 
        std::regex varInitializationRegex("(\\w+)=(\\w+)[;]");
        bool isVarInitialization = std::regex_match(str, matches, varInitializationRegex);
        isVarInitialization ? commandType = COMMAND_TYPE::VAR_INITIALIZATION : COMMAND_TYPE::UNDEFINED;
        isVarInitialization ? found = true : found = false;
    }

    //VAR_DEFINITION 3
    if (found == false)
    {
        std::regex varDefinitionRegex("(\\w+)(\\s)(\\w+)=(\\w+)[;]");
        bool isVarDefinition = std::regex_match(str, matches, varDefinitionRegex);
        isVarDefinition ? commandType = COMMAND_TYPE::VAR_DEFINITION : COMMAND_TYPE::UNDEFINED;
        isVarDefinition ? found = true : found = false;
    }

    //FUNC_DEFINITION 4
    if (found == false)
    {
        std::regex funcDefinitionRegex("(\\w+)(\\s)(\\w+)([(])(.*)([)])");
        bool isfuncDefinition = std::regex_match(str, matches, funcDefinitionRegex);
        isfuncDefinition ? commandType = COMMAND_TYPE::FUNC_DEFINITION : COMMAND_TYPE::UNDEFINED;
        isfuncDefinition ? found = true : found = false;
    }

    //FUNC_EXECUTION 5
    if (found == false)
    {
        std::regex funcExecuteRegex("(\\w+)([(])(.*)([)])([;])");
        bool isFuncExecute = std::regex_match(str, matches, funcExecuteRegex);
        isFuncExecute ? commandType = COMMAND_TYPE::FUNC_EXECUTION : COMMAND_TYPE::UNDEFINED;
        isFuncExecute ? found = true : found = false;
    }

    //FUNC_DECLARATION 6
    if (found == false)
    {
        std::regex funcDeclarationRegex("(\\w+)(\\s)(\\w+)([(])(.*)([)])([;])");
        bool isFuncDeclaration = std::regex_match(str, matches, funcDeclarationRegex);
        isFuncDeclaration ? commandType = COMMAND_TYPE::FUNC_DECLARATION : COMMAND_TYPE::UNDEFINED;
        isFuncDeclaration ? found = true : found = false;
    }
    /*
*   COMMAND OF COMMAND TYPE CREATION
*   */


    //ALL TO VECTOR
    std::cout << (int)commandType << std::endl;
    std::cout << "Matches(" << matches.size() << "):" << std::endl;
    std::vector<std::string> matches_vec;
    for (size_t i = 0; i < matches.size(); i++)
    {
        std::ssub_match sub_match = matches[i];
        std::string ssub_match = sub_match.str();
        std::cout << "Match " << i << ": " << ssub_match << std::endl;
        matches_vec.push_back(ssub_match);
    }
    std::cout << "\n";
    
    
    switch((int)commandType)
    {
        //VAR
        case 1:
        {
            CommandVarDeclaration cmdVarDeclaration;
            cmdVarDeclaration.commandType = commandType;
            cmdVarDeclaration.varType = matches_vec[1];
            usedVarNames.push_back(matches_vec[2]);
            cmdVarDeclaration.varDeclarationId = (int)usedVarNames.size();
            cmdVarDecList.push_back(cmdVarDeclaration);
            commandList.push_back(std::make_shared<CommandVarDeclaration>(cmdVarDecList.back()));
           
        }   
        break;

        case 2:
        {
            CommandVarInitialization cmdVarInitalization;
            cmdVarInitalization.commandType = commandType;
            cmdVarInitalization.varData=matches_vec[2];
            cmdVarInitalization.varDeclarationId=0; //TODO
            cmdVarInitList.push_back(cmdVarInitalization);
            commandList.push_back(std::make_shared<CommandVarInitialization>(cmdVarInitList.back()));
        }
        break;

        case 3:
        {
            CommandVarDefinition cmdVarDefinition;
            cmdVarDefinition.commandType=commandType;
            cmdVarDefinition.varData = matches_vec[4];
            cmdVarDefinition.varDeclarationId = 0; //TODO
            cmdVarDefinition.varType = matches_vec[1];
            cmdVarDefList.push_back(cmdVarDefinition);
            commandList.push_back(std::make_shared<CommandVarDefinition>(cmdVarDefList.back()));
        }
        break;
        
        //FUNC
        case 4:
        {
            CommandFuncDefinition cmdFuncDefinition;
            
        }
        break;

        case 5:
        {
            CommandFuncExecution cmdFuncExecution;
        }
        break;

        case 6:
        {
            CommandFuncDeclaration cmdFuncDeclaration; 
        }
        break;

        ////OTHER
        //case COMMAND_TYPE::UNDEFINED:
        //    break;

        default:

        break;
    }
}

std::string CommandTree::commandTypeIdToString(int id)
{
    if (id == 1) return "VAR_DECLARATION";
    else if (id == 2) return "VAR_INITIALIZATION";
    else if (id == 3) return "VAR_DEFINITION";
    else if (id == 4) return "FUNC_DEFINITION";
    else if (id == 5) return "FUNC_EXECUTION";
    else if (id == 6) return "FUNC_DECLARATION";
    return "UNDEFINED";
}

void CommandTree::displayCommandTree()
{
    std::cout << "\n\nCommandTree:" << std::endl;
    for (size_t i = 0; i < commandList.size(); i++)
    {
        std::cout << commandTypeIdToString((int)commandList[i]->commandType) << std::endl;

        ////VAR_DECLARATION
        //if(commandList[i]->commandType==COMMAND_TYPE::VAR_DECLARATION)
        //{ 
        //    auto cvd = commandList[i];
        //    std::cout << "varType: " << cvd->varType << ", varDeclarationId: " << cvd->varDeclarationId << std::endl;
        //}
        ////VAR_INITIALIZATION
        //else if (commandList[i]->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
        //{
        //    auto cvd = commandList[i];
        //    std::cout << "varData: "<< cvd->varData << std::endl;
        //}
        ////VAR_DEFINITION
        //else if (commandList[i]->commandType == COMMAND_TYPE::VAR_DEFINITION)
        //{
        //    auto cvd = commandList[i];
        //    std::cout << "varType: " << cvd->varType << ", varData: " << cvd->varData << std::endl;
        //}
        //FUNC_DEFINITION
        //FUNC_EXECUTION
        //FUNC_EXECUTION
    }

    for (size_t i = 0; i < cmdVarDecList.size(); i++)
    {
        std::cout << cmdVarDecList[i].varDeclarationId << std::endl;
    }
    
}

std::vector<std::string> createParametersVec(std::string& params)
{
    std::vector<std::string> parameters;
    return parameters;
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