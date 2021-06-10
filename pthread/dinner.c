/*************************************************************************
	> File Name: dinner.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Wed 09 Jun 2021 02:51:59 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#define PHLNUM 5

pthread_mutex_t mut_ch[PHLNUM];

inline static int getLeft(int x) {
    return (x + 4) % PHLNUM;
}

inline static int getRight(int x) {
    return (x + 1) % PHLNUM;
} 

void *phr_fun(void *p) {

    int id = (int)p;
    int left = getLeft(id);
    int right = getRight(id);
    
    while (1) {
        sleep(rand() % 10);
        pthread_mutex_lock(&mut_ch[left]);
        
        while (pthread_mutex_trylock(&mut_ch[right])) {
            pthread_mutex_unlock(&mut_ch[left]);
            sched_yield();
            pthread_mutex_lock(&mut_ch[left]);
        }
        printf("philosopher[%c] is eating!\n", 'A' + id);
        pthread_mutex_unlock(&mut_ch[left]);
        pthread_mutex_unlock(&mut_ch[right]);
        
        sleep(rand() % 10);
    }
    pthread_exit(NULL);
}


int main(){
    srand(time(NULL));
    pthread_t philo[PHLNUM];
    int err;

    for (int i = 0; i <PHLNUM; i++) {
        pthread_mutex_init(mut_ch+i, NULL);
    }

    for (int i = 0; i < PHLNUM; i++) {
        err = pthread_create(philo + i, NULL, phr_fun, (void *)i);
        if (err) {
            fprintf(stderr, "pthread_create:%s\n", strerror(err));
            exit(1);
        }
    }
    
    for (int i = 0; i < PHLNUM; i++) {
        pthread_join(philo[i], NULL);
    }

	return 0;
}
