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
        printf(taskName_.c_str());
        Sleep(2000);
        return 0;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    ThreadTaskPool threadPool(15);

    MyTask taskObj[3000];
    for (int i = 0; i < 3000; i++)
    {
        taskObj[i].SetAutoRelease(false);
        char ch[50] = { 0 };
       
        if (i%3 == 0)
        {
            _snprintf_s(ch, 50, _TRUNCATE, "优先任务id %d\r\n", i);
            taskObj[i].SetPriority(ITask::High);
        }
        else if(i % 10 == 0)
        {
            _snprintf_s(ch, 50, _TRUNCATE, "实时任务id %d\r\n", i);
            taskObj[i].SetPriority(ITask::Realtime);
        }
        else
        {
            _snprintf_s(ch, 50, _TRUNCATE, "普通任务id %d\r\n", i);
        }
        taskObj[i].setName(ch);
        threadPool.addTask(&taskObj[i]);
    }
    threadPool.start();
    while (true)
    {
        ::Sleep(100);
        //printf("there are still %d tasks need to process\n", threadPool.taskNum());
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

