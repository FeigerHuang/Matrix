/*************************************************************************
	> File Name: mydaemon.c
	> Author:Feiger Huang 
	> Mail:1162006607@qq.com 
	> Created Time: Fri 26 Mar 2021 08:28:57 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#define FNAME "/tmp/out"

static int daemonize(void) {
    pid_t pid;
    int fd;
    pid = fork();
    if (pid < 0) {
        perror("fork()");
        return -1;
    }
    
    if (pid > 0){ // parent
        exit(0);
    }
    fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        perror("open()");
        return -1;
    }
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    setsid();

    chdir("/");
//    umask(0);
    return 0;
}

int main(){
    
    FILE *fp;

    if(daemonize()) {
        exit(1);
    }

    fp = fopen(FNAME, "w");
    if(fp == NULL) {
        perror("fopen()");
        exit(1);
    }
    
    for(int i = 0;1; i++){
        fprintf(fp, "%d", i);
        fflush(fp);
        sleep(1);
    }

	return 0;
}
