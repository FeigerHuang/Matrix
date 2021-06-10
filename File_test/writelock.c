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
    fd = open("./hello.text", O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    
    if (fstat(fd, &sta) < 0 ) {
        perror("fstat");
        exit(1);
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_pid = getpid();
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sta.st_size;
    
    printf("pid: %d ",lock.l_pid);
    while (fcntl(fd, F_SETLK, &lock) < 0) {
        perror("fcntl");
        struct flock lock_1;
        lock_1 = lock;
        lock_1.l_type = F_WRLCK;
        fcntl(fd, F_GETLK, &lock_1);
        switch(lock_1.l_type) {
            case F_UNLCK:
                printf("unlocked\n");
                break;
            case F_RDLCK:
                printf("get read lock of pid = %d\n",lock_1.l_pid);
                break;
            case F_WRLCK:
                printf("get write lock of pid = %d\n", lock_1.l_pid);
        }
        sleep(1);
    }
    close(fd);
    
    printf("add write lock successfully\n"); 
	sleep(100);

    return 0;
}
