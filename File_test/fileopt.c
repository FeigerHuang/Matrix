/*************************************************************************
	> File Name: fileopt.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 15 May 2021 03:17:40 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    

    FILE *fp;
    fp = fopen("hello.text", "r+");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }

    fputc('A', fp);
    fputc('b', fp);
    fputc('c', fp);
    printf("pos = %ld\n", ftell(fp));   
    //rewind(fp);
    fseek(fp, -3, SEEK_END);
    
    printf("pos = %ld\n", ftell(fp));   

    fputc('X', fp);
    fputc('Y', fp);

    fclose(fp);

	return 0;
}
