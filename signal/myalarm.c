/*************************************************************************
	> File Name: myalarm.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sun 30 May 2021 05:09:14 PM CST
 ************************************************************************/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void nothing() {
    return;
}

unsigned int myalarm(unsigned int sec) {
    struct sigaction oldact, newact;
    newact.sa_flags = 0;
    newact.sa_handler = nothing;
    sigemptyset(&newact.sa_mask);

    sigaction(SIGALRM, &newact, &oldact);
    
    alarm(sec);
    
    pause();
    
    sigaction(SIGALRM, &oldact, NULL);
    
    unsigned int least = alarm(0);
    
    return least;
}

int main(){
    
    int n = 5;
    while(n--) {
        myalarm(2);
        printf("wait 2 second\n");
    }

	return 0;
}
