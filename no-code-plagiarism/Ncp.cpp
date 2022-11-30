#include "Ncp.h"

Ncp::Ncp()
{

}

bool Ncp::checkPlagiarismOfFiles(const std::string& pathToOrginalFile, const std::string& pathToCopyFile)
{
    std::ifstream original(pathToOrginalFile);
    std::ifstream copy(pathToCopyFile);

    std::string line = "";
    /*while (std::getline(original, line))
    {
        std::cout << line << std::endl;
    }*/
    
    original.close();
    copy.close();
    return true;
}

Ncp::~Ncp()
{

}
