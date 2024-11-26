#include "kernel/types.h"
#include "user/user.h"

#define RD 0    //pipe read
#define WR 1    //pipe write

int main(){
    char buf = 'P';  // 修改为单个字符

    int fd_c2p[2], fd_p2c[2];

    pipe(fd_c2p);
    pipe(fd_p2c);

    int pid = fork();
    int exit_status = 0;

    if(pid < 0){
        fprintf(2, "fork failed\n");
        close(fd_c2p[RD]);
        close(fd_c2p[WR]);
        close(fd_p2c[RD]);
        close(fd_p2c[WR]);
        exit(1);
    }else if(pid == 0){
        //child process
        close(fd_c2p[WR]);
        close(fd_p2c[RD]);
        // sleep(1);
        if(read(fd_c2p[RD], &buf, sizeof(char)) != sizeof(char)){
            fprintf(2, "read failed\n");
            exit_status = 1;
            exit(exit_status);
        }else{
            printf("%d: received ping\n", getpid());
        }
        if (write(fd_p2c[WR], &buf, sizeof(char)) != sizeof(char)) {
            fprintf(2, "write failed\n");
            exit_status = 1;
            exit(exit_status);
        }
        close(fd_c2p[RD]);
        close(fd_p2c[WR]);
        exit_status = 0;
        exit(exit_status);
    }else{
        //parent process
        close(fd_c2p[RD]);
        close(fd_p2c[WR]);

        if (write(fd_c2p[WR], &buf, sizeof(char)) != sizeof(char)) {
            fprintf(2, "write failed\n");
            exit_status = 1;
            exit(exit_status);
        }
        if (read(fd_p2c[RD], &buf, sizeof(char)) != sizeof(char)) {
            fprintf(2, "read failed\n");
            exit_status = 1;
            exit(exit_status);
        } else {
            printf("%d: received pong\n", getpid());
        }
        close(fd_c2p[WR]);
        close(fd_p2c[RD]);
        wait(&exit_status);
        exit_status = 0;
        exit(exit_status);
    }
    
}