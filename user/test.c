#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/pstat.h"

int
main(int argc, char *argv[])
{
    struct pstat st;

    if(argc != 2){
        printf("usage: mytest counter");
        exit(0);
    }

    int i, x, l, j;
    int mypid = getpid();

    for(i = 1; i < atoi(argv[1]); i++){
        x = x + i;
    }

    getprocinfo(&st);
    printf("returned from func\n");
    for (j = 0; j < NPROC; j++) {
        if (st.inuse[j] && st.pid[j] >= 3 && st.pid[j] == mypid) {
            for (l = 3; l >= 0; l--) {
                printf("level:%d \t ticks-used:%d\n", l, st.ticks[j][l]);
            }
        }
    }
    exit(0);
}