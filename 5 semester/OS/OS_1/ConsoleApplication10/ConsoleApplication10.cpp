// ConsoleApplication10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define DIV 4096
#define WIDTH 7
MEMORYSTATUS stat;
SYSTEM_INFO si;

int _tmain(int argc, _TCHAR* argv[])
{
	GetSystemInfo(&si);
	printf("\nThere are %lu pages in paging file.\n",
		WIDTH, stat.dwTotalPageFile / DIV);
	char c = getchar();
	return 0;
}

