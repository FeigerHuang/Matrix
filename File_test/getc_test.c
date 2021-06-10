/*************************************************************************
	> File Name: getc_test.c
	> Author:Feiger Huang 
	> Mail:1162006607@qq.com 
	> Created Time: Sun 07 Feb 2021 01:41:17 PM CST
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>

int main() {
    char ch;
    FILE *fp;
    FILE *p;
    fp = fopen("openfile.txt","r");
    p = fopen("putc.test","w");
    while ((ch = getc(fp))!= EOF){
        putc(ch, p);
        fprintf(stdout,"%c", ch);
    }
    
    fprintf(stdout,"done bye!");
    return 0;
}
