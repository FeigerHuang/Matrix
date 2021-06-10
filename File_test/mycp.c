/*************************************************************************
	> File Name: mycp.c
	> Author: Feiger
	> Mail:1162006607@qq.com 
	> Created Time: Sat 15 May 2021 04:11:37 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc < 3) {
        fprintf(stderr, "Usage...\n");
        exit(0);
    }
    
    FILE *fs = fopen(argv[1], "r");
    if (fs == NULL) {
        perror("fopen()");
        exit(1);
    }
    
    FILE *fd = fopen(argv[2], "w");
    if (fd == NULL) {
        perror("fopen()");
        exit(1);
    }

    int ch;
    while ((ch = fgetc(fs))!=EOF) {
        fputc(ch, fd);
    }


    fclose(fs);
    fclose(fd);

	return 0;
}
