#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void child(int priority){
    int pid;
    pid = getpid();
    set_cfs_priority(priority);
    for(int i = 0;i<1000000;++i){
            if(i%100000==0){
                sleep(1);
            }
    }
    int array[] = {0,0,0,0};
    get_cfs_stats(pid,(uint64)&array);
    //printf("PID is %d\n", pid);
    //printf("cfs_priority is %d\n", array[0]);
    //printf("run time is %d\n", array[1]);
    //printf("sleep time is %d\n", array[2]);
    //printf("runnable time is %d\n", array[3]);
    sleep(priority*3);
    printf("pid: %d, factor : %d, run time: %d, sleep time: %d, runnable time: %d\n",pid,array[0],array[1],array[2],array[3]);
}
int main(int argv, char* argc[]){
    int pid;
    if((pid=fork())==0){
        child(0);
    }
    if((pid=fork())==0){
        child(1);
    }
    if((pid=fork())==0){
        child(2);
    }
    wait(0,0);
    wait(0,0);
    wait(0,0);
    return 0;
}