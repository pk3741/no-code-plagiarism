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
    std::vector<std::tuple<long,std::string>> compareCommandTrees(CommandTree&, CommandTree&); //return tuple vector <long line number, string info>
    void setCommandTreeComutations(CommandTree&);
    bool compareCommand(std::shared_ptr<Command>&, std::shared_ptr<Command>&);
    ~Ncp();
    
};

#endif

