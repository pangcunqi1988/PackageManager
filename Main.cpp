#include <stdio.h>
#include <windows.h>
#include "PackageMgr.h"

int main()
{
	DWORD dwBeginTime = GetTickCount();
	g_objPackageMgr.InitPackage("ini");
	printf("[%d]InitPackage Over...\n", GetTickCount()-dwBeginTime);
	getchar();
	return 0;
}