/*************************************************************************
	> File Name: raiseopt.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 29 May 2021 03:53:13 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
    

    sleep(2);
    
    abort();
    //raise(SIGSEGV);

	return 0;
}
