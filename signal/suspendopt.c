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
    sigset_t newMask, oldMask, susMask;
    
    
    //阻塞闹钟信号
    sigemptyset(&newMask);
    sigaddset(&newMask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newMask, &oldMask);
    
    //替换alarm信号处理动作;
    newact.sa_handler = sig_alarm;
    newact.sa_flags = 0;
    sigemptyset(&newact.sa_mask);
    
    sigaction(SIGALRM, &newact, &oldact); 
    
    //开启闹钟;
    alarm(sec);
    
    //读取原来的信号屏蔽字情况;
    susMask = oldMask;
    //确保删除对Alarm信号的阻塞;
    sigdelset(&susMask, SIGALRM);
    //临时设置信号屏蔽字为susmask,并且挂起程序;
    sigsuspend(&susMask);
    perror("sigsuspend");

    //还原;
    int unslept;
    unslept = alarm(0);
    
    sigaction(SIGALRM, &oldact, NULL);
    sigprocmask(SIG_SETMASK, &oldMask, NULL);
    
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
