/*************************************************************************
	> File Name: ttyopt.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Mon 07 Jun 2021 03:01:46 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    
    int fd = open("./hello.txt", O_RDONLY);

    printf("out:%s\n", ttyname(STDOUT_FILENO));
    printf("in:%s\n", ttyname(STDIN_FILENO));
    printf("err:%s\n",ttyname(STDERR_FILENO));
    ttyname(fd);

	return 0;
}
