#ifndef _NO_CODE_PLAGIARISM_H
#define _NO_CODE_PLAGIARISM_H

#include <iostream>
#include <fstream>
#include <string>
#include "CommandTree.h"

class Ncp
{
public:
    Ncp();
    bool checkPlagiarismOfFiles(const std::string&,const std::string&); //load files using paths

    ~Ncp();
    
};

#endif

