/*************************************************************************
	> File Name: handle.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sun 30 May 2021 03:48:37 PM CST
 ************************************************************************/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void undead(int signo) {
    printf("get signo = %d, I'am fine, I'am alive\n", signo);
    return;
}

int main(){
    struct sigaction newact, oldact;
    newact.sa_handler = undead; 
    sigemptyset(&newact.sa_mask);
    
    sigaction(SIGINT, &newact, &oldact);
    int n = 20;
    while (n--){
        sleep(1);
    }
	return 0;
}
