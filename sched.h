//
// Created by 吴佳仪 on 2020/11/21.
//

#ifndef SYSTEM_SOFTWARE_SCHED_H
#define SYSTEM_SOFTWARE_SCHED_H

#include <list>
#include <queue>
#include "proc.h"

struct proc;





void enqueue();

void scheduleRR ();

void scheduleFCFS (bool* change);

#endif //SYSTEM_SOFTWARE_SCHED_H
