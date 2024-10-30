#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(){
    uint size=memsize();
    printf("process size: %d\n",size);
    char* pointer=malloc (20000);
    uint curr_size=memsize();
    printf("process size after malloc: %d\n",curr_size);
    free(pointer);
    uint size_after_free=memsize();
    printf("process size after free: %d\n",size_after_free);
    exit(0,"\0");
    
}