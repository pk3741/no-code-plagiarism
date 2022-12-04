#include "Ncp.h"

Ncp::Ncp()
{

}

bool Ncp::checkPlagiarismOfFiles(const std::string& pathToOrginalFile, const std::string& pathToCopyFile)
{
    std::ifstream original(pathToOrginalFile);
    std::ifstream copy(pathToCopyFile);

    std::string line = "";
    // buildCommandTree(original);
    // buildCommandTree(copy);
    
    original.close();
    copy.close();
    return true;
}



Ncp::~Ncp()
{

}
