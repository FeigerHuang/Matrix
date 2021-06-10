/*************************************************************************
	> File Name: testd.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Mon 07 Jun 2021 03:37:21 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    
    if (pid == 0) {
        pid_t sid = setsid(); 
        printf("new session id is %d\n", sid);
        
        if (chdir("/") < 0) {
            perror("chdir");
            exit(1);
        }
        close(0);
        int fd = open("/dev/null", O_RDWR);
        dup2(fd, 0);
        dup2(fd, 1);
        dup2(fd, 2);
        
        while (1) {
            sleep(1);
            printf("I am daemon, I am sleeping\n");
        }
    }

    printf("parent exit!\n");

	return 0;
}
