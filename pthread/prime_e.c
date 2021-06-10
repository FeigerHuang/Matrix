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
#define THRNUM (RIGHT - LEFT + 1)

struct thr_arg_st {
    int n;
};

static void *thr_prime(void *);

int main(){
    
    int i, j, mark;
    pthread_t tid[THRNUM];
    struct thr_arg_st *p;
    void *ptr;

    for (i = LEFT; i <= RIGHT; i++) {
        p = malloc(sizeof(struct thr_arg_st));
        if (p == NULL) {
            perror("malloc");
            exit(0);
        }
        p->n = i;
        
        int err = pthread_create(tid + i - LEFT, NULL, thr_prime, p);
        if (err) {
            fprintf(stderr, "pthread_create:%s\n", strerror(err));
            exit(1);
        }
    }

    for (int i = LEFT; i <= RIGHT; i++)
    {   pthread_join(tid[i-LEFT], &ptr);
        free(ptr);
    }

    return 0;
}

static void *thr_prime(void *p){
    int i;

    i = ((struct thr_arg_st *)p)->n;

    int mark = 1;
    for (int j = 2; j <= i / j; j++) {
        if (i % j == 0) {
            mark = 0;
            break;
        }
    }
    if (mark)
    printf("%d is a primer\n", i);


	pthread_exit(p);
}
