/*************************************************************************
	> File Name: cond.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sun 06 Jun 2021 11:44:30 AM CST
 ************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct Goods {
    int data;
    struct Goods *next;
} Goods;

Goods *head = NULL;
pthread_mutex_t headlock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t hasGoods = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    Goods *ng;
    while (1) {
        ng = (Goods *)malloc(sizeof(Goods));
        ng->data = rand() % 100;
        
        pthread_mutex_lock(&headlock);
        
        // head_insert;
        ng->next = head;
        head = ng;
        
        pthread_mutex_unlock(&headlock);
        pthread_cond_broadcast(&hasGoods);
        
        printf("produce %d\n", ng->data);
        sleep(rand()%3);
    }
}

void *consumer(void *arg) {
    Goods *k;
    while (1) {
        pthread_mutex_lock(&headlock);
        while (head == NULL) {
            pthread_cond_wait(&hasGoods, &headlock);
        }
        k = head;
        head = head->next;
        
        printf("consum %d\n", k->data);
        free(k);
        
        pthread_mutex_unlock(&headlock);
        sleep(rand() % 3);
    }
}

int main(){
    srand(time(NULL));
    pthread_t  pid, cid;
    
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

	return 0;
}
