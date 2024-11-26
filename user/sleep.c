#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[]){

    if(argc != 2){    //检查参数错误
        fprintf(2, "Usage: sleep <time>\n");
        exit(1);
    }

    sleep(atoi(argv[1]));
    exit(0);
}