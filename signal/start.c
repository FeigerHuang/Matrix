/*************************************************************************
	> File Name: start.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 29 May 2021 07:34:53 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void int_handle(int s) {

    write(1, "!", 1);
}

int main(){
   
    //signal(SIGINT, SIG_IGN);
    signal(SIGINT, int_handle);

    for (int i = 0; i < 10; i++) {
        
        write(1, "*", 1);
        sleep(1);
    }

	return 0;
}
