// Threadpool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ThreadTaskPool.h"

class MyTask
    :public ITask
{
public:
    MyTask(){
    }

    int run()
    {
        printf("hello world\r\n");
        Sleep(10);
        return 0;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    ThreadTaskPool threadPool(10);
    threadPool.start();
    MyTask taskObj[200];

    for (int i = 0; i < 200; i++)
    {
        taskObj[i].SetAutoRelease(false);
        threadPool.addTask(&taskObj[i]);
    }
    
    while (true)
    {
        ::Sleep(100);
        printf("there are still %d tasks need to process\n", threadPool.taskNum());
        if (threadPool.taskNum() == 0)
        {
            threadPool.stop();
            printf("Now I will exit from main\n");
            break;
        }
    }
    getchar();
    return 0;
}

