#include "Ncp.h"

Ncp::Ncp()
{

}

bool Ncp::checkPlagiarismOfFiles(const std::string& pathToOrginalFile, const std::string& pathToCopyFile)
{
    std::ifstream original(pathToOrginalFile);
    CommandTree originalCommandTree;

    std::ifstream copy(pathToCopyFile);

    std::string line = "";
    while (std::getline(original, line))
    {
        //skips
        if(line=="") continue;
        if(line[0]=='#') continue;
        if(line.find("main()")!=-1) continue;
        if(line=="{" || line=="}") continue;

        originalCommandTree.addCommand(line);
    }
    
    originalCommandTree.displayCommandTree();

    original.close();
    copy.close();
    return true;
}


Ncp::~Ncp()
{

}
