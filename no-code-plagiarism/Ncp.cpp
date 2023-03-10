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
    setCommandTreeComutations(originalCommandTree);
    displaySpares(originalCommandTree);
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
            std::dynamic_pointer_cast<CommandStatement>(actualCommandTree->getCommandListPtrVec().back()).get()->subCommands->setParent(actualCommandTree);
            actualCommandTree = std::dynamic_pointer_cast<CommandStatement>(actualCommandTree->getCommandListPtrVec().back()).get()->subCommands;
            actualCommandTree->inLoop = true;
        }
    
        if (line == "}")
        {
            actualCommandTree->inLoop = false;
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
            //if spare
            if (!checkForComutation(ct.getCommandListPtrVec()[i], ct.getCommandListPtrVec()[j], ct))
            {
                /*std::cout << i << " " << j << ": " << "spare" << std::endl;*/
                dest->at(i).push_back((long)j);
            }
            else //if not spare
            {
                /*std::cout << i << " " << j << ": " << "not-spare break" << std::endl;*/
                break;
            } 
        } 
    }
}

void Ncp::displaySpares(const CommandTree& ct)
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
bool Ncp::checkForComutation(const std::shared_ptr<Command> lhs, const std::shared_ptr<Command> rhs, CommandTree& ct) 
{
    auto lhsType = lhs.get()->commandType;
    auto rhsType = rhs.get()->commandType;

    if (lhsType == COMMAND_TYPE::VAR_DECLARATION)
    {
       //skip
    }
    else if (lhsType == COMMAND_TYPE::VAR_DEFINITION)
    {
        auto lhsCasted = std::dynamic_pointer_cast<CommandVarDefinition>(lhs);
        if (rhsType == COMMAND_TYPE::VAR_INITIALIZATION)
        {
            auto rhsCasted = std::dynamic_pointer_cast<CommandVarInitialization>(rhs);
            
            if (lhsCasted.get()->varDeclarationId == rhsCasted.get()->varDeclarationId)
            {
                return true;
            }
            else
            {
                return false;
            }
            lhsCasted = nullptr;
            rhsCasted = nullptr;
        }
        if (rhsType == COMMAND_TYPE::VAR_DEFINITION) // var_def with var_def
        {
            auto rhsCasted = std::dynamic_pointer_cast<CommandVarDefinition>(rhs);
            
            int lhsId = lhsCasted.get()->varDeclarationId;
            std::string rhsRhs = rhsCasted.get()->varData;
            std::string lhsRhs = lhsCasted.get()->varData;
            std::cout << "\t" << lhsCasted.get()->varDeclarationId << " " << rhsCasted.get()->varDeclarationId << std::endl;
           
            std::smatch matches1;
            std::regex rhsRegex("(\\w+)");
            
            //get rhs values of rhs and get theirs id:
            //rhs values
            std::vector<std::string> matches_vec; //rhs matches from vardata
            std::string::const_iterator itt = rhsRhs.cbegin();
            while (std::regex_search(itt, rhsRhs.cend(), matches1, rhsRegex))
            {
                matches_vec.push_back(matches1[0]);
                itt = matches1.suffix().first;
            }

            //for (int i = 0; i < matches_vec.size(); i++)
            //{
            //    std::cout << matches_vec[i] << std::endl;
            //}
    
            //theirs id
            std::vector<int> matches_vec_ids;
            CommandTree* actual = &ct;
            while (actual != nullptr)
            {
                for (auto const& match : matches_vec)
                {
                    for (size_t i = 0; i < actual->usedVarNames.size(); i++)
                    {

                        if (std::get<0>(actual->usedVarNames[i]) == match)
                        {
                            matches_vec_ids.push_back(std::get<1>(actual->usedVarNames[i]));
                            break;
                        }
                    }
                }
                actual = ct.parent;
            }


            for (int i = 0; i < matches_vec_ids.size(); i++)
            {
                if (matches_vec_ids[i] == lhsCasted.get()->varDeclarationId)
                {
                    return true;
                }
            }
        }
        return false;
    }
    else if (lhsType == COMMAND_TYPE::VAR_INITIALIZATION)
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
    }
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
