#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argv, char* argc[]){
 int pid = fork();
    if (pid==0){
        set_cfs_priority(0);
        for(int i=0;i<10;++i){
            sleep(1);
            for(int j=0;j<100000000;++j){}
        }
         pid = getpid();
        int array[] = {0,0,0,0};
        get_cfs_stats(pid,(uint64)&array);
        printf("PID is %d ", pid);
        printf("cfs_priority is %d ", array[0]);
        printf("run time is %d ", array[1]);
        printf("sleep time is %d ", array[2]);
        printf("runnable time is %d\n", array[3]);
        return 0;
    }
     pid = fork();
    if (pid==0){
        set_cfs_priority(2);
                for(int i=0;i<10;++i){
            sleep(1);
            for(int j=0;j<100000000;++j){}
                }
         pid = getpid();
        int array[] = {0,0,0,0};
        get_cfs_stats(pid,(uint64)&array);
        sleep(25);
        printf("PID is %d ", pid);
        printf("cfs_priority is %d ", array[0]);
        printf("run time is %d ", array[1]);
        printf("sleep time is %d ", array[2]);
        printf("runnable time is %d\n", array[3]);
        return 0;
    }
    pid = fork();
    if (pid==0){
        set_cfs_priority(1);
        for(int i=0;i<10;++i){
            sleep(1);
            for(int j=0;j<100000000;++j){}
                }
         pid = getpid();
        int array[] = {0,0,0,0};
        get_cfs_stats(pid,(uint64)&array);
        sleep(70);
        printf("PID is %d ", pid);
        printf("cfs_priority is %d ", array[0]);
        printf("run time is %d ", array[1]);
        printf("sleep time is %d ", array[2]);
        printf("runnable time is %d\n", array[3]);
        return 0;
    }
    for(int i=0;i<3;++i){
        wait(0,0);
    }
    return 0;

    }