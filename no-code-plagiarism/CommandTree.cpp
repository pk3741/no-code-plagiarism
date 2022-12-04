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
    //for(size_t i=0; i<commandList.size(); i++)
    
}

CommandTree::~CommandTree()
{

}