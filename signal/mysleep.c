/*************************************************************************
	> File Name: mysleep.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sun 30 May 2021 04:21:40 PM CST
 ************************************************************************/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void sig_alarm(int signo) {
    return ;
}

unsigned int mysleep(unsigned int sec) {
    struct sigaction newact, oldact;
    newact.sa_handler = sig_alarm;
    newact.sa_flags = 0;
    sigemptyset(&newact.sa_mask);
    
    sigaction(SIGALRM, &newact, &oldact); 
    
    alarm(sec);
    pause();

    int unslept;
    unslept = alarm(0);
    
    sigaction(SIGALRM, &oldact, NULL);

    return unslept;
}

int main(){
    
    int n = 5;
    while (n--) {
        printf("hello my sleep 1 sec\n");
        mysleep(1);
    }

	return 0;
}
