#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"



uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  
  char ptr [32];
  argstr(1,ptr,32);                         //my code for new exit implementation

  exit(n,ptr);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  uint64 ptr;
  argaddr(0, &p);
  argaddr(1,&ptr);
  //char* buff;

  //copyout(myproc()->pagetable,,buff,32);                  //i added this for new implementation

  return wait(p,ptr);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
uint64
sys_memsize(void)
{
// from here you can call other function in the kernal from proc.c or trap.c and many others places
  
  uint addr;
  addr=myproc()->sz;
  return addr;
}

uint64
sys_set_ps_priority(void){
  int n;
  argint(0,&n);
  struct proc *p=myproc();
  acquire(&p->lock);
  p -> priority = n;
  release(&p->lock);
  printf("my priority is: %d",p->priority);
  return 0;
}


uint64
 sys_set_policy(void){
  int n;
  argint(0,&n);

  if(!(n == 0 || n == 1 || n == 2))
    return -1;
  return set_policy_function(n);
  
}
uint64
  sys_set_cfs_priority(void){
    int n;
    argint(0,&n);
    if(!(n == 0 || n == 1 || n == 2))
      return -1;
    return set_cfs_priority(n);

  }
uint64
  sys_get_cfs_stats(void){
    int n;
    argint(0,&n);
    uint64 address;
    argaddr(1,&address);
    get_cfs_stats(n,address);
    return 0;

  }