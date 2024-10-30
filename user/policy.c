#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc<2){
        printf("no policy number was given!!!");
        return -1;
    }
    int policy = atoi(argv[1]);
    if(set_policy(policy)==-1){
        printf("something went wrong with the given policy, try again");
        return -1;
    }
    else{
        return 0;
    }
    
}