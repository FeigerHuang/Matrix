/*************************************************************************
	> File Name: abcd.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 05 Jun 2021 11:13:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define THRNUM 4
static pthread_mutex_t mut[THRNUM];

static int next(int n) {
    if (n + 1 == THRNUM)
        return 0;
    return n + 1;
}

static void *thr_fun(void *p) {
    int n = (int)p;
    int c = 'a' + (int)p;
    while(1) {
        pthread_mutex_lock(mut + n);
        write(1, &c, 1);
        pthread_mutex_unlock(mut+next(n));
    }

    pthread_exit(NULL);
}

int main(){
    
    pthread_t tid[THRNUM];

    for (int i = 0; i < THRNUM; i++) {
        pthread_mutex_init(mut+i, NULL);
        pthread_mutex_lock(mut+i); 
        int err = pthread_create(tid + i, NULL, thr_fun, (void *)i);
        if (err) {
            fprintf(stderr, "pthread_create:%s\n",strerror(err));
            exit(1);
        }
    }
    
    pthread_mutex_unlock(mut+0);

    alarm(5);
    for (int i = 0; i < THRNUM; i++){
        pthread_join(tid[i], NULL);
    }
	return 0;
}
