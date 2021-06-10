/*************************************************************************
	> File Name: myprime.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Tue 08 Jun 2021 04:43:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define LEFT 3000000
#define RIGHT 3000300
#define MAX_N 3500000
#define THRNUM 5
static int num = 0;
static int prime[MAX_N];
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;


static void *thr_prime(void *p) {
    int i;
    
    while (1) { 
        if (num == -1) break;

        pthread_mutex_lock(&mut_num);
        
        while (num == 0) {
            pthread_mutex_unlock(&mut_num);
            sched_yield();
            pthread_mutex_lock(&mut_num);
        }
        i = num;
        num = 0;
        
        pthread_mutex_unlock(&mut_num);
            
        for (int k = 2; k <= i; k++) {
            if (prime[k]) continue;
            for (int j = 2; k * j <= i; j++) {
                prime[k *j] = 1;
            }
        } 
        
        if (!prime[i])
            printf("[%d] : %d is  prime\n", 
                   (int)p,  i);
    }
    
    pthread_exit(NULL);

}


int main(){
    
    pthread_t tid[THRNUM];

    for (int i = 0; i < THRNUM; i++) {
        int err = pthread_create(tid+i, NULL, thr_prime, (void *)i);
        if (err) {
            fprintf(stderr, "pthread_create:%s\n",
                   strerror(err));
            exit(1);
        }
    }
    
    for (int i = LEFT; i <= RIGHT; i++) {
        pthread_mutex_lock(&mut_num);
        while (num != 0 ) {
            pthread_mutex_unlock(&mut_num);
            sched_yield();
            pthread_mutex_lock(&mut_num);
        }
        num = i;
        pthread_mutex_unlock(&mut_num);
    }
    
    num = -1;

    for (int i = 0; i < THRNUM; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mut_num);

	return 0;
}
