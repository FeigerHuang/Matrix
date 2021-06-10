/*************************************************************************
	> File Name: creat2.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Wed 09 Jun 2021 09:05:54 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *func(void *p) {
    int i;
    printf("address=%p\n",&i);
    while (1) {
        pause();
    }
    
}

int main(){
    pthread_t tid;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);    // 设置每个线程stack大小1024M
    int no = pthread_attr_setstacksize(&attr, 1024*1024*1024);
    if (no) {
        fprintf(stderr, "pthread_attr_setstacksize error\n");
        exit(1);
    }

    int i;
    for (i = 0; ; i++) {
        int err = pthread_create(&tid, &attr, func, NULL);
        if (err) {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            break;
        }
    }
    
    printf("In my environment max pthread = %d\n", i);
    
    pthread_attr_destroy(&attr);

	return 0;
}
