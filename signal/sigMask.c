/*************************************************************************
	> File Name: sigMask.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sun 30 May 2021 01:58:32 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_sig(const sigset_t *set) {
    int i;
    for ( i = 1; i < 32; i++) {
        if (sigismember(set, i)) {
           printf("%d sig is exit pending\n", i); 
        }
    }
}

int main(){
    sigset_t set, oldset, pset;
    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT); 
    
    sigprocmask(SIG_BLOCK, &set, &oldset);
    
    int n = 100;
    while (n--) {
        sigpending(&pset);
        print_sig(&pset);
        sleep(1);
    }

    sigprocmask(SIG_SETMASK, &oldset, NULL);
    
	return 0;
}
