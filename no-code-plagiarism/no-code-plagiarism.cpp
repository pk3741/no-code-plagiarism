﻿#include <iostream>
#include "Ncp.h"
#include <crtdbg.h>

int main()
{
    Ncp plagiat;
    plagiat.checkPlagiarismOfFiles("test_sets/set1/test1.cpp", "test_sets/set1/test2.cpp");
    _CrtDumpMemoryLeaks();
}
