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

    std::vector<std::tuple<int, int>> comparation = compareCommandTrees(originalCommandTree, copyCommandTree);
    std::cout << "\nComparation:\n";
    int count_good = 0;
    for (auto i : comparation)
    {
        std::cout << std::get<0>(i) << " " << std::get<1>(i) << std::endl;
        if(std::get<1>(i)==1) count_good++;
    }
    std::cout << "Total comperasion result: " << ((float)count_good/(float)comparation.size())*100 << "%" << std::endl;
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
            && line != "}")
        {
            //std::cout << "startloop" << std::endl;
            std::dynamic_pointer_cast<CommandStatement>(actualCommandTree->getCommandListPtrVec().back()).get()->subCommands->setParent(actualCommandTree);
            actualCommandTree->inLoop = true;
            actualCommandTree = std::dynamic_pointer_cast<CommandStatement>(actualCommandTree->getCommandListPtrVec().back()).get()->subCommands;
            actualCommandTree->inLoop = true;
        }

        if (line == "}")
        {
            //std::cout << "endloop" << std::endl;
            actualCommandTree->inLoop = false;
            actualCommandTree = actualCommandTree->parent;
        }

    }
    return globalCT;
}

void Ncp::setCommandTreeComutations(CommandTree& ct)
{
    auto* dest = &ct.comutations; //pointer to comutations vector, each index is related to command index in command list
    size_t commandListSize = ct.getCommandListPtrVec().size();
    //std::cout << commandListSize << std::endl;
    dest->resize(commandListSize);
    //iterate over all commands in command tree
    for (size_t i = 0; i < commandListSize; i++)
    {
        for (size_t j = i + 1; j < commandListSize; j++)
        {
            //std::cout << i << " " << j << std::endl;
            //if spare
            if (!checkForComutation(ct.getCommandListPtrVec()[i], ct.getCommandListPtrVec()[j], ct))
            {
                std::cout << i << " " << j << ": " << "spare" << std::endl;
                dest->at(i).push_back((long)j);
            }
            else //if not spare
            {
                std::cout << i << " " << j << ": " << "not-spare break" << std::endl;
                break;
            }
        }
    }
}

void Ncp::displaySpares(const CommandTree& ct)
{
    std::cout << "\n" << std::endl;
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
bool Ncp::checkForComutation(std::shared_ptr<Command> lhs, std::shared_ptr<Command> rhs, CommandTree& ct)
{

    auto lhsType = lhs.get()->commandType;
    auto rhsType = rhs.get()->commandType;
    //std::cout << (int)lhsType << " " << (int)rhsType << std::endl;
    if (lhsType == COMMAND_TYPE::VAR_DECLARATION)
    {
        //skip
    }
    else if (lhsType == COMMAND_TYPE::VAR_DEFINITION)
    {
        auto lhsCasted = std::dynamic_pointer_cast<CommandVarDefinition>(lhs);
        if (rhsType == COMMAND_TYPE::VAR_INITIALIZATION)
        {
            //LHS: var_definiton RHS: ^
            auto rhsCasted = dynamic_cast<CommandVarInitialization*>(rhs.get());

            if (lhsCasted->varDeclarationId == rhsCasted->varDeclarationId && lhsCasted.get()->parent == rhsCasted->parent) //+RHS CHECK
            {
                return true;
            }
            else
            {
                //rhsrhs check
                //if rhs ids == lhs ids then true else false
                std::string rhsRhs = rhsCasted->varData;
                //std::cout << "\t" << lhsCasted.get()->varDeclarationId << " " << rhsCasted.get()->varDeclarationId << std::endl;

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
                return false;
            }
            lhsCasted = nullptr;
            rhsCasted = nullptr;
        }
        if (rhsType == COMMAND_TYPE::VAR_DEFINITION) // var_def with var_def
        {
            //LHS: var_definiton RHS: ^
            auto rhsCasted = std::dynamic_pointer_cast<CommandVarDefinition>(rhs);

            int lhsId = lhsCasted.get()->varDeclarationId;
            std::string rhsRhs = rhsCasted.get()->varData;
            std::string lhsRhs = lhsCasted.get()->varData;
            //std::cout << "\t" << lhsCasted.get()->varDeclarationId << " " << rhsCasted.get()->varDeclarationId << std::endl;

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
            return false;
        }
        else if (rhsType == COMMAND_TYPE::STMT_FOR || rhsType == COMMAND_TYPE::STMT_IF || rhsType == COMMAND_TYPE::STMT_WHILE)
        {
            //LHS: var_definiton RHS: ^
            //if in rhs is changed lhs true else false
            auto toCheckId = lhsCasted.get()->varDeclarationId;
            auto toCheckParent = lhsCasted.get()->parent;
            auto rhsCasted = std::dynamic_pointer_cast<CommandStatement>(rhs);

            for (auto i : rhsCasted.get()->subCommands->getCommandListPtrVec())
            {
                if (i.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
                {
                    auto iCasted = std::dynamic_pointer_cast<CommandVarInitialization>(i);
                    if (iCasted.get()->varDeclarationId == toCheckId && lhsCasted.get()->parent == iCasted.get()->parent)
                    {
                        return true;
                    }
                }
                else if (i.get()->commandType == COMMAND_TYPE::STMT_FOR || i.get()->commandType == COMMAND_TYPE::STMT_IF || i.get()->commandType == COMMAND_TYPE::STMT_WHILE)
                {
                    return checkForComutation(lhs, std::dynamic_pointer_cast<Command>(i), ct);
                }

            }
            return false;

        }
        return true;
    }
    else if (lhsType == COMMAND_TYPE::VAR_INITIALIZATION)
    {
        auto lhsCasted = std::dynamic_pointer_cast<CommandVarInitialization>(lhs);
        if (rhs.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
        {
            auto rhsCasted = std::dynamic_pointer_cast<CommandVarInitialization>(rhs);
            if (lhsCasted.get()->varDeclarationId == rhsCasted.get()->varDeclarationId && lhsCasted.get()->parent == rhsCasted.get()->parent)
            {
                return true;
            }
            else
            {
                //lhs rhs == rhs rhs -> true : false //doesnt need because dont like to change places of var initialization
                return false;
            }
        }
        else if (rhs.get()->commandType == COMMAND_TYPE::VAR_DEFINITION)
        {
            return checkForComutation(rhs, lhs, ct);
        }
        /* else if (rhsType == COMMAND_TYPE::STMT_FOR || rhsType == COMMAND_TYPE::STMT_IF || rhsType == COMMAND_TYPE::STMT_WHILE)
         {
             auto rhsCasted = std::dynamic_pointer_cast<CommandStatement>(rhs);
             bool returnable = false;
             for (auto cmd : rhsCasted.get()->subCommands->getCommandListPtrVec())
             {
                 if (cmd.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
                 {
                     auto cmdCasted = std::dynamic_pointer_cast<CommandVarInitialization>(cmd);
                     if (cmdCasted.get()->parent == lhsCasted.get()->parent)
                     {
                         return true;
                     }
                 }
             }
             return false;
         }*/
        return true;

    }
    else if (lhsType == COMMAND_TYPE::STMT_FOR)
    {
        //LHS: STMT_FOR RHS: ^
        auto lhsCasted = std::dynamic_pointer_cast<CommandStatementFor>(lhs);
        if (rhsType == COMMAND_TYPE::STMT_FOR)
        {
            bool check = false;
            auto rhsCasted = std::dynamic_pointer_cast<CommandStatementFor>(rhs);
            for (auto i : lhsCasted.get()->subCommands->getCommandListPtrVec())
            {
                for (auto j : rhsCasted.get()->subCommands->getCommandListPtrVec())
                {
                    std::cout << (int)i.get()->commandType << " " << (int)j.get()->commandType << std::endl;
                    return checkForComutation(i, j, ct);//!tocheck
                    std::cout << check << std::endl;
                }

            }
            return check;
        }
        else if (rhsType == COMMAND_TYPE::VAR_INITIALIZATION)
        {
            for (auto i : lhsCasted.get()->subCommands->getCommandListPtrVec())
            {
                return checkForComutation(i, rhs, ct);
            }
        }
        else if (rhsType == COMMAND_TYPE::VAR_DEFINITION)
        {
            for (auto i : lhsCasted.get()->subCommands->getCommandListPtrVec())
            {
                return checkForComutation(i, rhs, ct);
            }
        }

    }
    else if (lhsType == COMMAND_TYPE::STMT_IF) //!tocheck
    {
        //LHS: STMT_IF RHS: ^
        auto lhsCasted = std::dynamic_pointer_cast<CommandStatementIf>(lhs);
        if (rhsType == COMMAND_TYPE::STMT_IF)
        {
            auto rhsCasted = std::dynamic_pointer_cast<CommandStatementIf>(rhs);
            for (auto i : lhsCasted.get()->subCommands->getCommandListPtrVec())
            {
                for (auto j : rhsCasted.get()->subCommands->getCommandListPtrVec())
                {
                    if (i.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION && j.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
                    {
                        auto iCasted = std::dynamic_pointer_cast<CommandVarInitialization>(i);
                        auto jCasted = std::dynamic_pointer_cast<CommandVarInitialization>(j);
                        std::cout << iCasted.get()->parent << " " << jCasted.get()->parent << std::endl;
                        if (iCasted.get()->parent == jCasted.get()->parent)
                        {

                            return true;
                        }
                    }
                }
            }
            return false;
        }

    }
    else if (lhsType == COMMAND_TYPE::STMT_WHILE) //!tocheck
    {
        //LHS: STMT_WHILE RHS: ^
        auto lhsCasted = std::dynamic_pointer_cast<CommandStatementWhile>(lhs);
        if (rhsType == COMMAND_TYPE::STMT_WHILE)
        {
            auto rhsCasted = std::dynamic_pointer_cast<CommandStatementWhile>(rhs);
            for (auto i : lhsCasted.get()->subCommands->getCommandListPtrVec())
            {
                for (auto j : rhsCasted.get()->subCommands->getCommandListPtrVec())
                {
                    if (i.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION && j.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
                    {
                        auto iCasted = std::dynamic_pointer_cast<CommandVarInitialization>(i);
                        auto jCasted = std::dynamic_pointer_cast<CommandVarInitialization>(j);
                        std::cout << iCasted.get()->parent << " " << jCasted.get()->parent << std::endl;
                        if (iCasted.get()->parent == jCasted.get()->parent)
                        {

                            return true;
                        }
                    }
                }
            }
            return false;
        }

    }
    /*
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

bool Ncp::compareCommandTreesForConiunction(CommandTree& lhs, CommandTree& rhs)
{
    bool output = false;
    for (auto i : rhs.getCommandListPtrVec())
    {
        if (i.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
        {
            auto rhsSubcommandCasted = std::dynamic_pointer_cast<CommandVarInitialization>(i); //rhs command

            if (rhsSubcommandCasted.get()->parent != &rhs)
            {
                //std::cout << "rozne" << std::endl;
            }
            else
            {
                //std::cout << "same" << std::endl;
            }
        }
    }
    return output;
}

std::vector<std::tuple<int, int>> Ncp::compareCommandTrees(CommandTree& lhs, CommandTree& rhs)
{
    std::vector<std::tuple<int, int>> output;

    for (size_t i = 0; i < lhs.getCommandListPtrVec().size(); i++)
    {
        for (size_t j = 0; j < rhs.getCommandListPtrVec().size(); j++)
        {
            if (i == j)
            {
                int check = compareCommand(lhs.getCommandListPtrVec()[i], rhs.getCommandListPtrVec()[j], lhs, rhs, (int)i);
                std::tuple<int, int> tempTuple;
                tempTuple = std::make_tuple((int)i, check);
                output.push_back(tempTuple);
            }
        }
    }
    return output;
}

int Ncp::compareCommand(const std::shared_ptr<Command> lhs, const std::shared_ptr<Command> rhs, CommandTree& lhsct, CommandTree& rhsct, int lhsindex=0)
{
    if (lhs.get()->commandType != rhs.get()->commandType)
    {
        //return 0;
        if (lhsct.comutations.size() > 0)
        {
            std::vector<long>* icomutations = &lhsct.comutations[lhsindex];
            if(icomutations!=nullptr)
            {
                for (size_t i = 0; i < icomutations->size(); i++)
                {
                    if (compareCommand(lhs, rhsct.getCommandListPtrVec()[icomutations->at(i)], lhsct, rhsct, lhsindex))
                    {
                        //swap lhs with rhsct...
                        std::shared_ptr<Command> temp = lhsct.getCommandListPtrVec()[lhsindex];
                        lhsct.getCommandListPtrVec()[lhsindex] = lhsct.getCommandListPtrVec()[icomutations->at(i)];
                        lhsct.getCommandListPtrVec()[icomutations->at(i)] = temp;
                        //setCommandTreeComutations(lhsct);
                        return true;
                    }
                }
            }
        }
        return false;
    }
    else
    {
        if (lhs.get()->commandType == COMMAND_TYPE::VAR_INITIALIZATION)
        {
            auto lhsCasted = std::dynamic_pointer_cast<CommandVarInitialization>(lhs);
            auto rhsCasted = std::dynamic_pointer_cast<CommandVarInitialization>(rhs);
            if  (lhsCasted.get()->varData == rhsCasted.get()->varData && 
                lhsCasted.get()->varDeclarationId == rhsCasted.get()->varDeclarationId &&
                lhsCasted.get()->varData == rhsCasted.get()->varData
                )
            {
                return 1;
            }
            return 0;

        }
        else if (lhs.get()->commandType == COMMAND_TYPE::VAR_DEFINITION)
        {
            auto lhsCasted = std::dynamic_pointer_cast<CommandVarDefinition>(lhs);
            auto rhsCasted = std::dynamic_pointer_cast<CommandVarDefinition>(rhs);
            if  (lhsCasted.get()->varData == rhsCasted.get()->varData &&
                rhsCasted.get()->varType == rhsCasted.get()->varType &&
                lhsCasted.get()->varDeclarationId == rhsCasted.get()->varDeclarationId
                )
            {
                return 1;
            }
            return 0;
        }
        else if (lhs.get()->commandType == COMMAND_TYPE::STMT_FOR)
        {
            auto lhsCasted = std::dynamic_pointer_cast<CommandStatementFor>(lhs);
            auto rhsCasted = std::dynamic_pointer_cast<CommandStatementFor>(rhs);
            for (size_t i = 0; i < lhsCasted.get()->subCommands->getCommandListPtrVec().size(); i++)
            {
                for (size_t j = 0; j < rhsCasted.get()->subCommands->getCommandListPtrVec().size(); i++)
                {
                    if (i == j)
                    {
                        return compareCommand(lhsCasted.get()->subCommands->getCommandListPtrVec()[i], rhsCasted.get()->subCommands->getCommandListPtrVec()[i], *lhsCasted.get()->subCommands, *rhsCasted.get()->subCommands);
                    }
                }
            }

        }
        else if (lhs.get()->commandType == COMMAND_TYPE::STMT_IF)
        {
            auto lhsCasted = std::dynamic_pointer_cast<CommandStatementIf>(lhs);
            auto rhsCasted = std::dynamic_pointer_cast<CommandStatementIf>(rhs);
        }
        else if (lhs.get()->commandType == COMMAND_TYPE::STMT_WHILE)
        {
            auto lhsCasted = std::dynamic_pointer_cast<CommandStatementWhile>(lhs);
            auto rhsCasted = std::dynamic_pointer_cast<CommandStatementWhile>(rhs);
        }
        else
        {
            return -1;
        }
    }

}

Ncp::~Ncp()
{

}
