// WinMonitor.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "EtwMon.h"

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	CEtwMon Monitor;

	DWORD dwError = Monitor.Start();
	if (ERROR_SUCCESS == dwError)
	{
		printf("EtwMon Successed !\n");

		int iStop;
		std::cin >> iStop;
		Monitor.Stop();
	}
	else
	{
		printf("EtwMon failed: %x\n", dwError);
	}

	return 0;
}

