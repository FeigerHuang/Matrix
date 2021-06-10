/*************************************************************************
	> File Name: abc.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Wed 09 Jun 2021 01:23:07 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THRNUM 3


pthread_mutex_t mut_alpha[THRNUM]; 

void *thr_fun(void *p) {
    int i = (int)p;
    while(1) {
        pthread_mutex_lock(mut_alpha + i);
        char alpha = 'A' + i;
        fprintf(stdout, "%c", alpha);
        pthread_mutex_unlock(mut_alpha + (i + 1) % THRNUM);
    }
    pthread_exit(NULL);
}


int main(){
    pthread_t tid[THRNUM];


    for (int i = 0; i < THRNUM; i++) {
        pthread_mutex_init(mut_alpha + i, NULL);
        pthread_mutex_lock(mut_alpha + i);
        pthread_create(tid+i, NULL, thr_fun, (void *)i);
    }
    
    pthread_mutex_unlock(mut_alpha);

    alarm(1);

    for (int i = 0; i < THRNUM; i++) {
        pthread_join(tid[i], NULL);
    }

	return 0;
}
