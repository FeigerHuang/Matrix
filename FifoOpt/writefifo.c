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
#include <string.h>

int main(){
    
    char buf[20] = {"hello pipe!"};
    int n = strlen(buf);
    int fd = open("./tube", O_WRONLY);
    if (fd < 0) {
        perror("open()");
        exit(1);
    } 
    
    write(fd, buf, n);
    close(fd);
	return 0;
}
