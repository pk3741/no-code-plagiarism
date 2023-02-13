#include "CommandTree.h"

CommandTree::CommandTree(): variable_counter(0)
{

}

COMMAND_TYPE CommandTree::addCommand(std::string& str)
{
    return createCommand(str);
}

COMMAND_TYPE CommandTree::createCommand(std::string& str)
{
    COMMAND_TYPE commandType = COMMAND_TYPE::UNDEFINED;
    std::cout << "Line: " << str << std::endl;

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

    //STMT_FOR 7
    if (found == false)
    {
        std::regex stmtForRegex("(for)\\s*([(])(.*);(.*);(.*)([)])");
        
        bool isForStmt = std::regex_match(str, matches, stmtForRegex);
        isForStmt ? commandType = COMMAND_TYPE::STMT_FOR : COMMAND_TYPE::UNDEFINED;
        isForStmt ? found = true : found = false;
    }

    //STMT_WHILE 8
    if (found == false)
    {
        std::regex stmtWhileRegex("(while)([(])(.*)([)])");
        bool isWhileStmt = std::regex_match(str, matches, stmtWhileRegex);
        isWhileStmt ? commandType = COMMAND_TYPE::STMT_WHILE : COMMAND_TYPE::UNDEFINED;
        isWhileStmt ? found = true : found = false;
    }

    //STMT_IF 9
    if (found == false)
    {
        std::regex stmtIfRegex("(if)([(])(.*)([)])");
        bool isIfStmt = std::regex_match(str, matches, stmtIfRegex);
        isIfStmt ? commandType = COMMAND_TYPE::STMT_IF : COMMAND_TYPE::UNDEFINED;
        isIfStmt ? found = true : found = false;
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
            cmdVarDeclaration.varDeclarationId = variable_counter;
            usedVarNames.emplace_back(matches_vec[2],variable_counter, matches_vec[1]);
            variable_counter++;
            cmdVarDecList.push_back(cmdVarDeclaration);
            //commandList.push_back(std::make_shared<CommandVarDeclaration>(cmdVarDecList.back()));
           
        }   
        break;

        case 2:
        {
            CommandVarInitialization cmdVarInitalization;
            cmdVarInitalization.commandType = commandType;
            cmdVarInitalization.varData=matches_vec[2];
            
            for (size_t uvn_itt = 0; uvn_itt < usedVarNames.size(); uvn_itt++)
            {
                if (std::get<0>(usedVarNames[uvn_itt]) == matches_vec[1])
                {
                    cmdVarInitalization.varDeclarationId= std::get<1>(usedVarNames[uvn_itt]);
                    break;
                }
            }
            std::cout << cmdVarInitalization.varDeclarationId << std::endl;
            // set id here
            cmdVarInitList.push_back(cmdVarInitalization);
            commandList.push_back(std::make_shared<CommandVarInitialization>(cmdVarInitList.back()));
        }
        break;

        case 3:
        {
            CommandVarDefinition cmdVarDefinition;
            cmdVarDefinition.commandType=commandType;
            cmdVarDefinition.varData = matches_vec[4];
            cmdVarDefinition.varDeclarationId = variable_counter;
            usedVarNames.emplace_back(matches_vec[3], variable_counter, matches_vec[1]);
            variable_counter++;
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
        //STATEMENTS
        //FOR
        case 7:
        {
            CommandStatementFor cmdStatementFor;
            cmdStatementFor.start = matches[3];
            cmdStatementFor.stop = matches[4];
            cmdStatementFor.change = matches[5];
            cmdStatementFor.commandType = commandType;
            cmdStatementFor.subCommands = new CommandTree();
            cmdStmtForList.push_back(cmdStatementFor);
            commandList.push_back(std::make_shared<CommandStatementFor>(cmdStmtForList.back()));
        }
        break;

        //WHILE
        case 8:
        {
            CommandStatementWhile cmdStatementWhile;
            cmdStatementWhile.commandType = commandType;
            cmdStatementWhile.subCommands = new CommandTree();
            cmdStmtWhileList.push_back(cmdStatementWhile);
            commandList.push_back(std::make_shared<CommandStatementWhile>(cmdStmtWhileList.back()));
        }
        break;

        //IF
        case 9:
        {
            CommandStatementIf cmdStatementIf;
            cmdStatementIf.commandType = commandType;
            cmdStatementIf.subCommands = new CommandTree();
            cmdStmtIfList.push_back(cmdStatementIf);
            commandList.push_back(std::make_shared<CommandStatementIf>(cmdStmtIfList.back()));
        }
        break;

        ////OTHER
        //case COMMAND_TYPE::UNDEFINED:
        //    break;

        default:

        break;
    }
    return commandType;
}

std::string CommandTree::commandTypeIdToString(int id)
{
    if (id == 1) return "VAR_DECLARATION";
    else if (id == 2) return "VAR_INITIALIZATION";
    else if (id == 3) return "VAR_DEFINITION";
    else if (id == 4) return "FUNC_DEFINITION";
    else if (id == 5) return "FUNC_EXECUTION";
    else if (id == 6) return "FUNC_DECLARATION";
    else if (id == 7) return "STMT_FOR";
    else if (id == 8) return "STMT_WHILE";
    else if (id == 9) return "STMT_IF";
    return "UNDEFINED";
}

void CommandTree::displayCommandTree(std::string& prefix)
{
    if(prefix=="") std::cout << "\n\nCommandTree:" << std::endl;
    for (size_t i = 0; i < commandList.size(); i++)
    {
        auto cvd = commandList[i].get();
        //std::cout << (int)cvd->commandType << std::endl;
        switch (cvd->commandType)
        {
            case COMMAND_TYPE::VAR_DECLARATION:
            {
                auto cvd_dest = std::dynamic_pointer_cast<CommandVarDeclaration>(commandList[i]);
                std::cout << prefix << commandTypeIdToString((int)cvd_dest->commandType) << " " << cvd_dest->varDeclarationId << " " << cvd_dest->varType << std::endl;
                break;
            }
            case COMMAND_TYPE::VAR_DEFINITION:
            {
                auto cvd_dest = std::dynamic_pointer_cast<CommandVarDefinition>(commandList[i]);
                std::cout << prefix <<  commandTypeIdToString((int)cvd_dest->commandType) << " " << cvd_dest->varDeclarationId << " " << cvd_dest->varType << std::endl;
                break;
            }
            case COMMAND_TYPE::VAR_INITIALIZATION:
            {
                auto cvd_dest = std::dynamic_pointer_cast<CommandVarInitialization>(commandList[i]);
                std::cout << prefix <<  commandTypeIdToString((int)cvd_dest->commandType) << " " << cvd_dest->varDeclarationId << std::endl;
                break;
            }
            case COMMAND_TYPE::STMT_FOR:
            {
                std::string prefix = "\t";
                auto cvd_dest = std::dynamic_pointer_cast<CommandStatementFor>(commandList[i]);
                std::cout << commandTypeIdToString((int)cvd_dest->commandType) << std::endl;
                cvd_dest.get()->subCommands->displayCommandTree(prefix);

            }
            case COMMAND_TYPE::STMT_WHILE:
            {
                std::string prefix = "\t";
                auto cvd_dest = std::dynamic_pointer_cast<CommandStatementWhile>(commandList[i]);
                std::cout << commandTypeIdToString((int)cvd_dest->commandType) << std::endl;
                cvd_dest.get()->subCommands->displayCommandTree(prefix);
                break;
            }
            case COMMAND_TYPE::STMT_IF:
            {
                std::string prefix = "\t";
                auto cvd_dest = std::dynamic_pointer_cast<CommandStatementIf>(commandList[i]);
                std::cout << commandTypeIdToString((int)cvd_dest->commandType) << std::endl;
                cvd_dest.get()->subCommands->displayCommandTree(prefix);
            }
        }

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

    if (prefix == "")
    {
        std::cout << "\n\nVariable dictionary:\n";
        for (size_t i = 0; i < usedVarNames.size(); i++)
        {
            std::cout << std::get<0>(usedVarNames[i]) << " " << std::get<1>(usedVarNames[i]) << " " << std::get<2>(usedVarNames[i]) << std::endl;
        }
    }
    
}

CommandTree::~CommandTree()
{

}

std::vector<std::shared_ptr<Command>>& CommandTree::getCommandListPtrVec()
{
    return commandList;
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