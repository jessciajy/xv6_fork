#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/pstat.h"

#define check(exp, msg)                                                        \
  if (exp) {                                                                   \
  } else {                                                                     \
    printf( "%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg); \
    ;                                                                          \
  }

#define DDEBUG 1

#ifdef DDEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) \
  do {                 \
  } while (0)
#endif

// char buf[10000]; // ~10KB
int workload(int n, int t) {
  int i, j = 0;
  for (i = 0; i < n; i++) {
    j += i * j + 1;
  }

  if (t > 0) pause(t);
  for (i = 0; i < n; i++) {
    j += i * j + 1;
  }
  return j;
}

int sleepload(int n, int t) {
  int i;
  for (i = 0; i < n; i++) {
    printf("XV6_SCHEDULER\t Sleep\n");
    pause(1);
  }
  printf("XV6_SCHEDULER sleepload LOOP FINISHED! ready to exit\n");
  return i;
}

int main(int argc, char *argv[]) {
  struct pstat st;
  check(getprocinfo(&st) == 0, "getpinfo");

  // Push this thread to the bottom
  workload(100, 0);

  int i, j, k;

  // Launch the 4 processes, but process 2 will sleep in the middle
  for (i = 0; i < 1; i++) {
    int c_pid = fork();
    int t = 0;
    // Child
    if (c_pid == 0) {
      if (i % 2 == 1) {
        t = 64 * 5;  // for this process, give up CPU for one time-slice
      }
      sleepload(200, t);
      exit(0);
    } else {
      // setpri(c_pid, 2);
    }
  }

  for (i = 0; i < 12; i++) {
    pause(12);
    check(getprocinfo(&st) == 0, "getpinfo");

    for (j = 0; j < NPROC; j++) {
      if (st.inuse[j] && st.pid[j] >= 3 && st.pid[j] != getpid()) {
        DEBUG_PRINT(( "XV6_SCHEDULER\t CHILD\n"));
        // DEBUG_PRINT((1, "pid: %d\n", st.pid[j]));
        for (k = 3; k >= 0; k--) {
          DEBUG_PRINT(( "XV6_SCHEDULER\t \t level %d ticks used %d\n", k,
                       st.ticks[j][k]));
          DEBUG_PRINT(
              ("XV6_SCHEDULER\t \t level %d\n", k));
        }
      }
    }
  }


  // printf(1, "TEST PASSED");

  exit(0);
}