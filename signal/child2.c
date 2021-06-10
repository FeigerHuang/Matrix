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

void sig_child(int s) {
    int stat;
    pid_t pid = wait(&stat);
    if (WIFEXITED(stat)) {
        printf("proc(%d) :exit with code %d\n",pid, WIFEXITED(stat));
    }
    else {
        printf("lemon %d\n", WEXITSTATUS(stat));
    }

    return;
}

int main(){
    struct sigaction newAct, oldAct;

    pid_t pid = fork();
    

    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    
    if (pid) {
        printf("child1 = %d\n", pid);
        
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("fork time :2");
            exit(1);
        }

        if (pid2)  {
            printf("child2 = %d\n", pid2);
            newAct.sa_handler = SIG_IGN;
            newAct.sa_flags = 0;
            sigemptyset(&newAct.sa_mask);
            
            sigaction(SIGCHLD, &newAct, &oldAct);
            //sigsuspend(&oldAct.sa_mask);
            int n = 100;
            while (n--) {
                printf("work ~\n");
                sleep(1);
            }
        } else {
            sleep(5);
            exit(5);
        }
    } 
    else {
        sleep(3);
        exit(3);
    }

	return 0;
}
