#include "Ncp.h"

Ncp::Ncp()
{

}

bool Ncp::checkPlagiarismOfFiles(const std::string& pathToOrginalFile, const std::string& pathToCopyFile)
{
    std::ifstream original(pathToOrginalFile);
    std::vector<CommandTree>originalCommandTrees;

    std::ifstream copy(pathToCopyFile);
    std::string line = "";

    CommandTree globalCT;//global
    //CommandTree mainCT;//main()
    //CommandTree * actual = &globalCT;


    CommandTree* actualCommandTree = &globalCT;
    COMMAND_TYPE subCommandType;
    while (std::getline(original, line))
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

    std::string nullstr = "";
    globalCT.displayCommandTree(nullstr);
    original.close();
    copy.close();
    return true;
}


Ncp::~Ncp()
{

}
