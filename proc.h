//
// Created by 吴佳仪 on 2020/11/17.
//

#ifndef SYSTEM_SOFTWARE_PROC_H
#define SYSTEM_SOFTWARE_PROC_H

enum eventType{
    ARRIVALEVENT,
    FINISHEVENT,
    TIMEREVENT
};

enum proc_state {
    PROC_NotCreated,  // 尚未创建
    PROC_RUNNING,     // 运行
    PROC_RUNNABLE,       // 就绪
    PROC_FINISHED     // 完成
};

struct proc
{
    int pid;
    int createTime;
    int prio;
    int round;
    int cputime;
    int needtime;
    int count;
    int state;
} ;




#endif //SYSTEM_SOFTWARE_PROC_H