/*************************************************************************
	> File Name: part.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Wed 09 Jun 2021 01:36:38 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#define THRNUM 3
#define CARNUM 10
sem_t  sem_inport, sem_export;

int cnt = CARNUM;
pthread_mutex_t car_lock = PTHREAD_MUTEX_INITIALIZER;

int out_fun(int p) {
    int i = (int)p;

    if (sem_trywait(&sem_export) != 0){
        return 0;
    }
    printf("[%d] exprot a car\n", i);
    sem_post(&sem_inport);
    return 1;
}

int in_fun(int p) {
    int i = (int)p;
    
    if (sem_trywait(&sem_inport) != 0){
        return 0;
    } 
    printf("[%d] inport a car\n", i);
    sem_post(&sem_export);
    return -1;
}

void *pthr_fun(void *p) {
    int id = (int)p;
    
    while (1) {
        int opt = rand() % 2;
        int t;
        switch(opt) {
            case 0:{
                t = out_fun(id); 
            }break;
            case 1:{
                t = in_fun(id);
            }break;
        }
        if (t) {
            pthread_mutex_lock(&car_lock);
            printf("remain char position : %d\n", cnt += t);
            pthread_mutex_unlock(&car_lock);
        }
        sleep(opt+1);
    }
    
    pthread_exit(NULL);
}


int main(){
    srand(time(NULL));
    int err;    
    pthread_t intid[THRNUM];
    
    if (sem_init(&sem_inport, 0, CARNUM) < 0) {
        perror("sem_init()");
        exit(1);
    }

    if (sem_init(&sem_export, 0, 0) < 0) {
        perror("sem_init()");
        exit(1);
    }

    for (int i = 0; i < THRNUM; i++) {
        err = pthread_create(intid + i, NULL, pthr_fun, (void *)i); 
        if (err) {
            fprintf(stderr , "pthread_create():%s\n",strerror(err));
        }
    }


    for (int i = 0;i < THRNUM; i++) {
        pthread_join(intid[i], NULL);
    }
    
    sem_destroy(&sem_inport);
    sem_destroy(&sem_export);
	return 0;
}
