#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#include "Ncp.h"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Ncp plagiat;
    plagiat.checkPlagiarismOfFiles("test_sets/set1/test1.cpp", "test_sets/set1/test2.cpp");
    _CrtDumpMemoryLeaks();
    return 0;
}
