/*************************************************************************
	> File Name: readfifo.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Tue 25 May 2021 07:00:28 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
    
    char buf[20];
    int fd = open("./tube", O_RDONLY);
    if (fd < 0) {
        perror("open()");
        exit(1);
    } 
    perror("open()");  
    ssize_t n = read(fd, buf, 20);
    printf("read %ld bytes\n", n);

    write(1, buf, n);
    close(fd);
	return 0;
}
