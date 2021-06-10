/*************************************************************************
	> File Name: file_open.c
	> Author:Feiger Huang 
	> Mail:1162006607@qq.com 
	> Created Time: Sun 07 Feb 2021 01:25:37 PM CST
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>

int main() {
    int ch;
    FILE *fp;
    fp = fopen("openfile.txt", "a+");
    if (fp != NULL)
        printf("file open is ojbk!\n");
    else 
        printf("Error!\n");
    char words[1000];
    fscanf( stdin , "%s", words);
    fprintf( stdout , "%s has get, now write in openfile!",words);
    fprintf(fp,"%s",words);
    return 0;
}
