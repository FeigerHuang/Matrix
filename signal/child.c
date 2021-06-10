/*************************************************************************
	> File Name: child.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Wed 02 Jun 2021 04:35:53 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    struct sigaction newAct, oldAct;

    pid_t pid = fork();
    

    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    
    if (pid) {
        printf("child1 = %d\n", pid);
        newAct.sa_handler = SIG_IGN;
        newAct.sa_flags = 0;
        sigemptyset(&newAct.sa_mask);
        
        sigaction(SIGCHLD, &newAct, &oldAct);
        //sigsuspend(&oldAct.sa_mask);
        
        printf("SIG_IGN = %p\n", SIG_IGN);
        printf("old_handler = %p\n", oldAct.sa_handler);

        int n = 6;
        while (n--) {
            printf("work ~\n");
            sleep(1);
        }
    } 
    else {
        sleep(2);
        exit(1);
    }

	return 0;
}
