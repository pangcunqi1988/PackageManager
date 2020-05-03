#include <stdio.h>
#include <windows.h>
#include "PackageMgr.h"
#include "MemStack.h"

int main()
{
// ===============================
// 	HANDLE hLogFile = ::CreateFileA("MemoryCheck.txt", GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
// 	_CrtSetReportMode(_CRT_WARN ,_CRTDBG_MODE_FILE);
// 	_CrtSetReportFile(_CRT_WARN, hLogFile);
// 	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// ===============================
// 	_CrtMemState state;
// 	_CrtMemCheckpoint(&state);
// ===============================
// 	_CrtMemState state2;
// 	_CrtMemCheckpoint(&state2);
// 	_CrtMemState state3;
// 	_CrtMemDifference(&state3, &state, &state2);
// 	_CrtMemDumpStatistics(&state3);
// ===============================

	DWORD dwBeginTime = GetTickCount();
	g_objPackageMgr.InitPackage("ini");
	printf("[%d]InitPackage Over...\n", GetTickCount()-dwBeginTime);
	g_objPackageMgr.DestoryPackage();

	g_objMemStack.LogMemLeak();
	getchar();
	return 0;
}