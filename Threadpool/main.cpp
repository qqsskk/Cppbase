// Threadpool.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Sort.h"


int _tmain(int argc, _TCHAR* argv[])
{
    int a[8] = { 3, 1, 5, 7, 2, 4, 9, 6 };
    SortInsertShell(a, 8);
    print(a, 8, 8);
    getchar();
    return 0;
}

