/*************************************************************************
	> File Name: prime.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 05 Jun 2021 10:00:50 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4 

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;


static void *thr_prime(void *);

int main(){
    
    int i, j, mark;
    pthread_t tid[THRNUM];

    for (i = 0; i < THRNUM; i++) {
        int err = pthread_create(tid + i , NULL, thr_prime, (void *)i);
        if (err) {
            fprintf(stderr, "pthread_create:%s\n", strerror(err));
            exit(1);
        }
    }
    
    for (i = LEFT; i <= RIGHT; i++) {
        pthread_mutex_lock(&mut_num);
        while (num != 0) {
            pthread_mutex_unlock(&mut_num);
            sched_yield();
            pthread_mutex_lock(&mut_num);
        }
        
        num = i;
        pthread_mutex_unlock(&mut_num);
    }
    
    pthread_mutex_lock(&mut_num);
    while (num != 0) {
        pthread_mutex_unlock(&mut_num);
        sched_yield();
        pthread_mutex_lock(&mut_num);
    }
    num = -1;
    pthread_mutex_unlock(&mut_num);

    for (int i = 0; i < THRNUM; i++)
        pthread_join(tid[i], NULL);
    
    
    pthread_mutex_destroy(&mut_num);
    return 0;
}

static void *thr_prime(void *p){
    int i;

    while (1) {
        pthread_mutex_lock(&mut_num);
        while (num == 0) {
            pthread_mutex_unlock(&mut_num);
            sched_yield();
            pthread_mutex_lock(&mut_num);
        }
        if (num == -1) {
            pthread_mutex_unlock(&mut_num);
            break;
        }
        i = num;
        num = 0;
        pthread_mutex_unlock(&mut_num);
        int mark = 1;
        for (int j = 2; j <= i / j; j++) {
            if (i % j == 0) {
                mark = 0;
                break;
            }
        }
        if (mark)
        printf("[%d]%d is a primer\n", (int)p, i);
    }
    
	pthread_exit(NULL);
}
