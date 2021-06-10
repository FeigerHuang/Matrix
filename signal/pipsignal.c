/*************************************************************************
	> File Name: pipsignal.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 29 May 2021 03:57:54 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>


int main(){
    int pfd[2];

    if (pipe(pfd) < 0) {
        perror("pipe()");
        exit(1);
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork()");
        exit(1);
    }
    
    if (pid) {
        close(pfd[0]);
        close(pfd[1]);
        
        int sta;
        wait(&sta);
        if (WIFSIGNALED(sta)) {
            printf("signal = %d\n", WTERMSIG(sta)) ;
        }
        else{
            printf("exit other ways\n");
        }
    }
    else{
        sleep(3);
        close(pfd[0]);
        write(pfd[1], "hello\n", 6);
        sleep(10);
    }

	return 0;
}
