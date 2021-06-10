/*************************************************************************
	> File Name: main.c
	> Author:Feiger Huang 
	> Mail:1162006607@qq.com 
	> Created Time: Thu 04 Mar 2021 07:18:16 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(){
    void* handle;
    int (*ADD)(int, int);
    int (*SUB)(int, int);
    
    handle = dlopen("./lib_cal.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    ADD = dlsym(handle, "add");
    SUB = dlsym(handle, "sub");
    
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n%d\n", ADD(a, b), SUB(a, b));
    if (dlclose(handle) < 0) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
	return 0;
}
