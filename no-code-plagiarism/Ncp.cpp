#include "Ncp.h"

Ncp::Ncp()
{

}

bool Ncp::checkPlagiarismOfFiles(const std::string& pathToOrginalFile, const std::string& pathToCopyFile)
{
    std::ifstream original(pathToOrginalFile);
    std::ifstream copy(pathToCopyFile);

    std::string line = "";
    while (std::getline(original, line))
    {
        //skips
        if(line=="") continue;
        if(line[0]=='#') continue;
        if(line.find("main()")!=-1) continue;
        if(line=="{" || line=="}") continue;

        CommandTree originalCommandTree;
        originalCommandTree.addCommand(line);
    }
    
    original.close();
    copy.close();
    return true;
}



Ncp::~Ncp()
{

}
