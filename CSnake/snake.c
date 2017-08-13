/*
 * 父进程获取下一个方向
 *      发送方向信号给子进程
 *
 * 子进程接收信号，在自己的地址空间内改变方向
 * 完成移动
 * 子进程完成地图状态的绘制
 */

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

static int pos=1; // 默认向上

void handler_reaped(int sig){ // 回收子进程
    pid_t pid;

    while((pid = waitpid(-1, NULL, 0)) > 0){
        printf("Handler reaped child %d\n", (int)pid);
    }

    if(errno != ECHILD){
        unix_error("waitpid error");
    }
    return;
}

void handler_up(int sig){
    pos = 1;
}
void handler_down(int sig){
    pos = 2;
}
void handler_left(int sig){
    pos = 3;
}
void handler_right(int sig){
    pos = 4;
}


int main(){
    if((pid = fork()) == 0){
        signal(UP, handler_up);
        signal(DOWN, handler_down);
        signal(LEFT, handler_left);
        signal(RIGHT, handler_right);
        for(;;){
            print_map(pos);
            sleep(1);
        }
        exit();
    }

    if(signal(SIGCHLD, handler_reaped) == SIG_ERR){ // 设置SIGCHLE处理程序，回收子进程
        unix_error("waitfg: waitpid error");
    }

    for(;;){
        pos = getchar();
        if(feof(stdin)){
            exit(0);
        }
        kill(pid, pos); // 给子进程发送方向信号
    }
}
