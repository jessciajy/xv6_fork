// Demonstrate that moving the "acquire" in iderw after the loop that
// appends to the idequeue results in a race.

// For this to work, you should also add a spin within iderw's
// idequeue traversal loop.  Adding the following demonstrated a panic
// after about 5 runs of stressfs in QEMU on a 2.1GHz CPU:
//    for (i = 0; i < 40000; i++)
//      asm volatile("");

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  int fd, i;
  char path[] = "stressfs0";
  char data[512];

  printf("stressfs starting\n");
  memset(data, 'a', sizeof(data));
  // pid of the child proc is 0, because p->trapframe->a0 
  // is set to 0 in forkret() within proc.c
  // For proc0 (original proc), fork()>0 break
  // for proc1 forked from proc0, i =0, fork()=0, so i=1
  // Then fork() > 0, break.
  // for proc2 forked from proc1, i=1, fork()=0, so i=2
  // for proc3 forked from proc2, i=2, fork()=0, so i=3
  // for proc4 forked from proc3, i=3, fork()=0, so i=4
  // End
  for (i = 0; i < 4; i++)
    if (fork() > 0)
      break;

  printf("write %d\n", i);

  path[8] += i;
  fd = open(path, O_CREATE | O_RDWR);
  for (i = 0; i < 20; i++) {
    // printf(fd, "%d\n", i);
    write(fd, data, sizeof(data));
  }
  close(fd);

  printf("read\n");

  fd = open(path, O_RDONLY);
  for (i = 0; i < 20; i++)
    read(fd, data, sizeof(data));
  close(fd);

  wait(0);

  exit(0);
}
