/*************************************************************************
	> File Name: readlock.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Mon 07 Jun 2021 12:25:48 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    struct stat sta;
    int fd;
    fd = open("./hello.text", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    
    if (fstat(fd, &sta) < 0 ) {
        perror("fstat");
        exit(1);
    }

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_pid = getpid();
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sta.st_size;
    
    printf("pid: %d ",lock.l_pid);
    if (fcntl(fd, F_SETLK, &lock) < 0) {
        perror("fcntl");
        exit(1);
    }
    printf("add read lock successfully\n"); 
	
    
    sleep(10);

    return 0;
}
