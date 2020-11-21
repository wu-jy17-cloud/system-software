#include <iostream>
#include <list>
#include "proc.h"

using namespace std;

static int timer = 0;
static bool change = false;
bool needSched = false;

struct proc *cur;

list <proc>  ready_queue;
list <proc>  notCreated_queue;
list <proc>  finished_queue;


void scheduleRR () {

}

void scheduleFCFS (){
    while (notCreated_queue.front().createTime == timer) {
        notCreated_queue.front().state = PROC_RUNNABLE;
        ready_queue.push_back(notCreated_queue.front());
        notCreated_queue.pop_front();
        change = true;
    }

    if(cur && --cur->needtime == 0) {
        cur->state = PROC_FINISHED;
        finished_queue.push_back(*cur);
        cur = nullptr;
        needSched = true;
        change = true;
    }

    if ((!cur && !ready_queue.empty()) ||( needSched && !ready_queue.empty())) {
        cur = static_cast<proc *>(malloc(sizeof(struct proc)));
        cur->pid = ready_queue.front().pid;
        cur->state = PROC_RUNNING;
        cur->createTime = ready_queue.front().createTime;
        cur->needtime = ready_queue.front().needtime;
        cur->cputime = ready_queue.front().cputime;
        cur->count = ready_queue.front().count;
        cur->prio = ready_queue.front().prio;
        cur->round = ready_queue.front().round;

        ready_queue.pop_front();
        needSched = false;
        change = true;
    }
}

void print() {
    printf("After time %d:\n", timer);
    if (cur)
        printf("    RUNNING -> P%d\n", cur->pid);
    else
        printf("    RUNNING -> NULL\n");
    if (!ready_queue.empty()) {
        auto it1 = ready_queue.begin();
        printf("    ReadyQueue");
        while (it1 != ready_queue.end()){
            printf(" -> P%d", it1->pid);
            it1++;
        }
        printf("\n");
    } else
        printf("    ReadyQueue -> NULL\n");

    if (!notCreated_queue.empty()) {
        auto it2 = notCreated_queue.begin();
        printf("    NotCreated");
        while (it2 != notCreated_queue.end()){
            printf(" -> P%d", it2->pid);
            it2++;
        }
        printf("\n");
    } else
        printf("    NotCreated -> NULL\n");

    if (!finished_queue.empty()) {
        auto it3 = finished_queue.begin();
        printf("    Finished");
        while (it3 != finished_queue.end()){
            printf(" -> P%d", it3->pid);
            it3++;
        }
        printf("\n");
    } else
        printf("    Finished -> NULL\n");
}

int main() {
    char buff[255];
    int count;
    int pid;
    int createTime;
    int CPUTime;
    int timeSlice;
    FILE *fp = nullptr;
    fp = fopen("../test.txt", "r");
    fscanf(fp, "%s", buff);
    printf("%s\n", buff);
    string name = buff;

    fscanf(fp, "%d", &count);
    printf("%d\n", count);

    for (int i = 0 ; i < count; i++) {
        fscanf(fp, "%d %d %d", &pid, &createTime, &CPUTime);
        printf("%d %d %d\n", pid, createTime, CPUTime);

        struct proc tmp_proc = {pid, createTime,0,0,CPUTime,CPUTime,0, PROC_NotCreated};
        notCreated_queue.push_back(tmp_proc);
    }

    if (name == "RR") {
        fscanf(fp, "%d", &timeSlice);
        printf("%d\n", timeSlice);
        while (finished_queue.size() == count) {
            scheduleRR();
            if (change) {
                print();
                change = false;
            }
            timer++;
        }
    } else if (name  == "FCFS") {
        while (finished_queue.size() != count) {
            scheduleFCFS();
            if (change) {
                print();
                change = false;
            }
            timer++;
        }
    }

    fclose(fp);
    return 0;
}
