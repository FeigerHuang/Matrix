/*************************************************************************
	> File Name: killopt.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 29 May 2021 03:22:05 PM CST
 ************************************************************************/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid ) {
        sleep(3);
        
        if (kill(pid , SIGQUIT) < 0) {
            perror("kill()");
            exit(1);
        }
        int sta;
        wait(&sta);
        if (WIFSIGNALED(sta)) {
            printf("child terminate by signal %d\n",
                  WTERMSIG(sta));
        }
        else{
            printf("child exit with other reason\n");
        }
    }
    else {
        while (1) {
            printf("child sleep 1 sec\n");
            sleep(1);
        }
    }

	return 0;
}
