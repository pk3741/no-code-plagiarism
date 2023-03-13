#ifndef _NO_CODE_PLAGIARISM_H
#define _NO_CODE_PLAGIARISM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CommandTree.h"

class Ncp
{
public:
    Ncp();
    
    bool checkPlagiarismOfFiles(const std::string&,const std::string&); //load files using paths
    CommandTree createCommandTree(std::ifstream& file); //creates command tree
    std::vector<std::tuple<int,bool>> compareCommandTrees(CommandTree&, CommandTree&); //return tuple vector <long line number, string info>
    void setCommandTreeComutations(CommandTree&);
    bool checkForComutation(const std::shared_ptr<Command>, const std::shared_ptr<Command>, CommandTree&);
    bool compareCommandTreesForConiunction(CommandTree&, CommandTree&);
    bool compareCommand(const std::shared_ptr<Command>, const std::shared_ptr<Command>);
    void displaySpares(const CommandTree&);
    virtual ~Ncp();
    
};

#endif

