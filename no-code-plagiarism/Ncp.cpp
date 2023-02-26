#include "Ncp.h"

Ncp::Ncp()
{

}

bool Ncp::checkPlagiarismOfFiles(const std::string& pathToOrginalFile, const std::string& pathToCopyFile)
{
    std::string nullstr = "";
    std::ifstream original(pathToOrginalFile);
    CommandTree originalCommandTree = createCommandTree(original);
    std::cout << "ORIGINAL=====================================\n";
    originalCommandTree.displayCommandTree(nullstr);
    original.close();

    std::ifstream copy(pathToCopyFile);
    CommandTree copyCommandTree = createCommandTree(copy);
    std::cout << "\nCOPY=========================================\n";
    copyCommandTree.displayCommandTree(nullstr);
    copy.close();

    setCommandTreeComutations(originalCommandTree);
    return true;
}



CommandTree Ncp::createCommandTree(std::ifstream& file)
{
    CommandTree globalCT;//global
    //CommandTree mainCT;//main()
    //CommandTree * actual = &globalCT;


    CommandTree* actualCommandTree = &globalCT;
    std::string line = "";
    while (std::getline(file, line))
    {
        line = trimStr(line);
        //skips
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        if (line.find("main()") != -1) continue;
        if (line == "{" /*|| line == "}"*/) continue;

        actualCommandTree->addCommand(line);

        if (!actualCommandTree->getCommandListPtrVec().empty() &&
            (actualCommandTree->getCommandListPtrVec().back().get()->commandType == COMMAND_TYPE::STMT_FOR ||
            actualCommandTree->getCommandListPtrVec().back().get()->commandType == COMMAND_TYPE::STMT_WHILE ||
            actualCommandTree->getCommandListPtrVec().back().get()->commandType == COMMAND_TYPE::STMT_IF)
            )
        {
            std::dynamic_pointer_cast<CommandStatement>(actualCommandTree->getCommandListPtrVec().back()).get()->subCommands->setParent(actualCommandTree);
            actualCommandTree = std::dynamic_pointer_cast<CommandStatement>(actualCommandTree->getCommandListPtrVec().back()).get()->subCommands;
        }
    
        if (line == "}")
        {
            actualCommandTree = actualCommandTree->parent;
        }
        
    }
    return globalCT;
}

void Ncp::setCommandTreeComutations(CommandTree& ct)
{
    std::vector<std::vector<long>> * dest = &ct.comutations; //pointer to comutations vector, each index is related to command index in command list
    size_t commandListSize = ct.getCommandListPtrVec().size();
    //iterate over all commands in command tree
    for (size_t i = 0; i < commandListSize; i++)
    {   
        //i command
        auto iRawCommand = ct.getCommandListPtrVec()[i];

        //i command type
        COMMAND_TYPE iRawCommandType = iRawCommand.get()->commandType;  

        //casted i command to command
        switch (iRawCommandType)
        {
            case COMMAND_TYPE::VAR_DEFINITION:
            {
                auto iCommand = std::dynamic_pointer_cast<CommandVarDefinition>(iRawCommand);
                //iterate over all commands starting from next element ending when meet the condition
                for (size_t j = i+1; j < commandListSize; j++)
                {
                    //iterate to when does not more coniuncate
                    //TODO: funcs like comparetest(std::shared_ptr<CommandVarDefinition> cvd, std::shared<ptr>Command);
                }
                break;
            }
            case COMMAND_TYPE::VAR_DECLARATION:
            {
                auto iCommand = std::dynamic_pointer_cast<CommandVarDeclaration>(iRawCommand);
                break;
            }
            case COMMAND_TYPE::VAR_INITIALIZATION:
            {
                auto iCommand = std::dynamic_pointer_cast<CommandVarInitialization>(iRawCommand);
                break;
            }
            case COMMAND_TYPE::STMT_FOR:
            {
                auto iCommand = std::dynamic_pointer_cast<CommandStatementFor>(iRawCommand);
                break;
            }
            case COMMAND_TYPE::STMT_IF:
            {
                auto iCommand = std::dynamic_pointer_cast<CommandStatementIf>(iRawCommand);
                break;
            }
            case COMMAND_TYPE::STMT_WHILE:
            {
                auto iCommand = std::dynamic_pointer_cast<CommandStatementWhile>(iRawCommand);
                break;
            }
        }
        
        
        
    }
}

std::vector<std::tuple<long, std::string>> Ncp::compareCommandTrees(CommandTree& lhs, CommandTree& rhs)
{
    std::vector<std::tuple<long, std::string>> output;
    return output;
}

Ncp::~Ncp()
{

}
