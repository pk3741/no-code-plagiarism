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


    bool subCommand = false;
    COMMAND_TYPE subCommandType;
    while (std::getline(original, line))
    {
        line = trimStr(line);
        //skips
        if (line == "") continue;
        if (line[0] == '#') continue;
        if (line.find("main()") != -1) continue;
        if (line == "{" /*|| line == "}"*/) continue;

        if (!globalCT.getCommandListPtrVec().empty())
        {
            if (globalCT.getCommandListPtrVec().back().get()->commandType == COMMAND_TYPE::STMT_FOR ||
                globalCT.getCommandListPtrVec().back().get()->commandType == COMMAND_TYPE::STMT_WHILE ||
                globalCT.getCommandListPtrVec().back().get()->commandType == COMMAND_TYPE::STMT_IF
                )
            {
                subCommandType = globalCT.getCommandListPtrVec().back().get()->commandType;
                if (subCommandType == COMMAND_TYPE::STMT_FOR)
                {
                    bool cvd_dest = std::dynamic_pointer_cast<CommandStatementFor>(globalCT.getCommandListPtrVec().back()).get()->loopEnded;
                    if (cvd_dest == false)
                    {
                        subCommand = true;
                    }
                    
                }
                else if (subCommandType == COMMAND_TYPE::STMT_WHILE)
                {
                    bool cvd_dest = std::dynamic_pointer_cast<CommandStatementWhile>(globalCT.getCommandListPtrVec().back()).get()->loopEnded;
                    if (cvd_dest == false)
                    {
                        subCommand = true;
                    }
                    
                }
                else if (subCommandType == COMMAND_TYPE::STMT_IF)
                {
                    bool cvd_dest = std::dynamic_pointer_cast<CommandStatementIf>(globalCT.getCommandListPtrVec().back()).get()->loopEnded;
                    if (cvd_dest == false)
                    {
                        subCommand = true;
                    }
                    
                }
            }
        }

        if (subCommand == false)
        {
            globalCT.addCommand(line);
        }
        else
        {
            if (line == "}")
            {
                if (subCommandType == COMMAND_TYPE::STMT_FOR ||
                    subCommandType == COMMAND_TYPE::STMT_WHILE ||
                    subCommandType == COMMAND_TYPE::STMT_IF
                   )
                {
                    auto cvd_dest = std::dynamic_pointer_cast<CommandStatement>(globalCT.getCommandListPtrVec().back());
                    cvd_dest.get()->loopEnded = true;
                    subCommand = false;
                    std::cout << "here:" << cvd_dest.get()->loopEnded <<std::endl;
                }
            }
            else
            {
                if (subCommandType == COMMAND_TYPE::STMT_FOR ||
                    subCommandType == COMMAND_TYPE::STMT_WHILE ||
                    subCommandType == COMMAND_TYPE::STMT_IF
                   )
                {
                    auto cvd_dest = std::dynamic_pointer_cast<CommandStatement>(globalCT.getCommandListPtrVec().back());
                    //cvd_dest.get()->subCommands->addCommand(line);
                    globalCT.addSubCommand(line);
                }
            }
        }
    }

    //originalCommandTree.displayCommandTree();
    std::string nullstr="";
    globalCT.displayCommandTree(nullstr);

    original.close();
    copy.close();
    return true;
}


Ncp::~Ncp()
{

}
