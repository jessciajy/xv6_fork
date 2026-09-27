#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"



int
main(int argc, char *argv[])
{
    int master_pid = getpid();
  for (int i = 0; i < 200; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    }
    if (pid) {
      if (wait(0) != pid) {
        printf("wait wrong pid\n");
        exit(1);
      }
    } else {
      int pid2 = fork();
      if (pid2 < 0) {
        kill(master_pid);
        exit(1);
      }
      exit(0);
    }
  }
  printf("ready to exit 1\n");
  exit(0);
}