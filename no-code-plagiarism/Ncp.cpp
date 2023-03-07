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
            dynamic_cast<CommandStatement*>(actualCommandTree->getCommandListPtrVec().back().get())->subCommands->setParent(actualCommandTree);
            actualCommandTree = dynamic_cast<CommandStatement*>(actualCommandTree->getCommandListPtrVec().back().get())->subCommands;
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
    auto * dest = &ct.comutations; //pointer to comutations vector, each index is related to command index in command list
    size_t commandListSize = ct.getCommandListPtrVec().size();
    //std::cout << commandListSize << std::endl;
    dest->resize(commandListSize);
    //iterate over all commands in command tree
    for (size_t i = 0; i < commandListSize; i++)
    {   
        for (size_t j = i+1; j < commandListSize; j++)
        {
            /*
            //if spare
            if (!compareCommand(ct.getCommandListPtrVec()[i], ct.getCommandListPtrVec()[j]))
            {
                //std::cout << i << " " << j << ": " << "spare" << std::endl;
                dest->at(i).push_back((long)j);
            }
            else //if not spare
            {
                //std::cout << i << " " << j << ": " << "not-spare break" << std::endl;
                break;
            } 
            */
            
        } 
    }
}

void Ncp::displaySpares(CommandTree& ct)
{
    for (int i = 0; i < ct.comutations.size(); i++)
    {
        std::cout << "For line " << i << " lines:" << "\n";
        for (int j = 0; j < ct.comutations[i].size(); j++)
        {
            std::cout << ct.comutations.at(i).at(j) << "\n";
        }
    }
}

//comparasion for comutation
bool Ncp::compareCommand(std::unique_ptr<Command>& lhs, std::unique_ptr<Command>& rhs) 
{
    auto lhsType = lhs.get()->commandType;
    auto rhsType = rhs.get()->commandType;

    if (lhsType == COMMAND_TYPE::VAR_DECLARATION)
    {
       //skip
    }
    else if (lhsType == COMMAND_TYPE::VAR_DEFINITION)
    {
        auto lhsCasted = dynamic_cast<CommandVarDefinition*>(lhs.get());
        if (rhsType == COMMAND_TYPE::VAR_INITIALIZATION)
        {
            auto rhsCasted = dynamic_cast<CommandVarInitialization*>(rhs.get());
            
            if (lhsCasted->varDeclarationId == rhsCasted->varDeclarationId)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    /*else if (lhsType == COMMAND_TYPE::VAR_INITIALIZATION)
    {
        auto lhsCasted = std::dynamic_pointer_cast<CommandVarInitialization>(lhs);
    }
    if (lhsType == COMMAND_TYPE::STMT_FOR)
    {
        auto lhsCasted = std::dynamic_pointer_cast<CommandStatementFor>(lhs);
    }
    else if (lhsType == COMMAND_TYPE::STMT_IF)
    {
        auto lhsCasted = std::dynamic_pointer_cast<CommandStatementIf>(lhs);
    }
    else if (lhsType == COMMAND_TYPE::STMT_WHILE)
    {
        auto lhsCasted = std::dynamic_pointer_cast<CommandStatementWhile>(lhs);
    }*/
    return false;

}

std::vector<std::tuple<long, std::string>> Ncp::compareCommandTrees(CommandTree& lhs, CommandTree& rhs)
{
    std::vector<std::tuple<long, std::string>> output;
    return output;
}

Ncp::~Ncp()
{

}
