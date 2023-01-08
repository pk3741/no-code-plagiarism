#include "CommandTree.h"

CommandTree::CommandTree()
{

}

void CommandTree::addCommand(std::string& cmd)
{
    Command newCommand(cmd);
    commandList.push_back(newCommand);
}

void CommandTree::displayCommandTree()
{
    std::cout << "\n\nCommandTree:" << std::endl;
    for (size_t i = 0; i < commandList.size(); i++)
    {
        std::cout << (int)commandList[i].commandType << std::endl;
    }
    
}

CommandTree::~CommandTree()
{

}