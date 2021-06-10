/*************************************************************************
	> File Name: waitpid.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Wed 02 Jun 2021 04:22:26 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void my_handler(int s) {
    int stat;
    wait(&stat);
    printf("child stat = %d\n", stat);
}

int main(){
    pid_t pid;
    pid = fork();
    struct sigaction newAct, oldAct;
    sigset_t newMask, oldMask, susMask;

    sigemptyset(&newMask);
    sigaddset(&newMask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &newMask, &oldMask);

    newAct.sa_handler = my_handler;
    newAct.sa_flags = 0;
    sigemptyset(&newAct.sa_mask);
    
    sigaction(SIGCHLD, &newAct, &oldAct);

    if (pid == 0) {
        fprintf(stderr, "child has exit!\n");
        exit(2);
    }
    else{
        sigsuspend(&oldMask);
    } 

	return 0;
}
