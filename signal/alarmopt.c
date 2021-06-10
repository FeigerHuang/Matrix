/*************************************************************************
	> File Name: alarmopt.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 29 May 2021 04:22:14 PM CST
 ************************************************************************/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


int main(){

    alarm(5);
    sleep(3);
    unsigned int left = alarm(3);
    
    printf("left = %u\n", left);
   
    char i;
    for ( i = 120; i > -1; i++ ) {
        printf("i=%d\n", i);
    }
    
    printf("i = %d\n", i);

	return 0;
}
