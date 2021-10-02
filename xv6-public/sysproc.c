#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getc(void)
{
  return getc();
}

/* VGA-related syscalls */
int
sys_modeswitch(void)
{
  int n;
  if (argint(0, &n) == -1 || (n != 1 && n != 0)){
    return -1;
  }
  modeswitch(n);
  return 0;
}

int
sys_plotpixel(void)
{
  int x, y, color;
  if (argint(0, &x) == -1 || argint(1, &y) == -1 || argint(2, &color) == -1)
    return -1;
  if (x < 0 || x > 319 || y < 0 || y > 199 || color < 0 || color > 255)
    return -1;
  plotpixel(x, y, color);
  return 0;
}

int
sys_plotrectangle(void)
{
  int x1, y1, x2, y2, color;
  if (argint(0, &x1) == -1 || argint(1, &y1) == -1 ||
      argint(2, &x2) == -1 || argint(3, &y2) == -1 || argint(4, &color) == -1)
    return -1;
  if (x1 < 0 || x1 > 320 || y1 < 0 || y1 > 200 ||
      x2 < 0 || x2 > 320 || y2 < 0 || y2 > 200 ||
      color < 0 || color > 255 || x1 >= x2 || y1 >= y2)
    return -1;
  plotrectangle(x1, y1, x2, y2, color);
  return 0;
}

int
sys_printimage(void)
{
  int width, length, x, y, scale;
  char *bitmap;
  if (argint(0, &width) == -1 || argint(1, &length) == -1 || argint(2, &x) == -1 ||
      argint(3, &y) || argptr(4, &bitmap, width*length) || argint(5, &scale) == -1){
    return -1;
   }
   if(x<0 || y<0 || width<0 || length<0 || x+ scale*(width)>320 || y + scale*(length)>200){
     return -1;
   }
   for(int i=0; i<width*length; i++ ){
     if(bitmap[i]<0 || bitmap[i]>64){
       return -1;
     }
   }
  printimage(width, length, x, y, bitmap, scale);
  return 0;
}

int
sys_printchar(void)
{
  int c;
  int x, y, color, scale;
  if(argint(0, &c) == -1 || argint(1, &x) == -1 || argint(2, &y) == -1 ||
     argint(3, &color) == -1 || argint(4, &scale) == -1)
    return -1;
  if(x<0 || y<0 || color<0 || color>255 || scale < 0 ||
     x + scale*8>320 || y + scale*16>200)
    return -1;
  printchar((uchar)c, x, y, color, scale);
  return 0;
}