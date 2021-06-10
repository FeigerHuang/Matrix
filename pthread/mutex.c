/*************************************************************************
	> File Name: mutex.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 05 Jun 2021 08:48:48 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

volatile int cnt = 0;

pthread_mutex_t add_lock = PTHREAD_MUTEX_INITIALIZER;

void *cntadd(void *arg) {
    int val;

    for (int i = 0; i < 5000; i++) {
        pthread_mutex_lock(&add_lock);
        val = cnt;
        cnt = val + 1; 
        printf("%p: %d\n",(void *)pthread_self(), cnt);
        pthread_mutex_unlock(&add_lock);
    }
    return NULL;
}

int main(){
    
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, cntadd, NULL);
    pthread_create(&tid2, NULL, cntadd, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

	return 0;
}
