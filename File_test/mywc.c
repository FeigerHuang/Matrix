/*************************************************************************
	> File Name: mywc.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 15 May 2021 04:43:37 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
        
    if (argc < 1) {
        fprintf(stderr, "usage...\n");
        exit(0);
    }
    
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long long ind = ftell(fp);
    printf("%s size = %lld\n", argv[1], ind);

    fclose(fp);
	return 0;
}
