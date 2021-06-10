/*************************************************************************
	> File Name: compete.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Wed 09 Jun 2021 05:59:22 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THRNUM 20

static void *thr_add(void *p) {

}

int main(){
    
    pthread_t tid[THRNUM];
        
        
    for (int i = 0; i < THRNUM; i++) 
        pthread_join(tid[i], NULL);
	return 0;
}
