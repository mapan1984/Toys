/*
 * 内置命令quit结束进程
 * 后台命令以&结尾
 * 可运行同一目录下课执行目标文件
 */

#include "base.h"

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void unix_error(char *mag);

void handler(int sig){ // 回收后台运行命令的程序
    pid_t pid;

    while((pid = waitpid(-1, NULL, 0)) > 0){ // 不断的等待下一个SIGCHLD，直到无子进程, 返回-1
                                            // 无子进程是设置errno = ECHILD
        printf("Handler reaped child %d\n", (int)pid);
    }
    if(errno != ECHILD){ // 如果不是因为无子进程而结束while循环，则错误
        unix_error("waitpid error");
    }
    return;
}

int main(){
    char cmdline[MAXARGS];

    for(;;){
        /* 打印提示符 */
        printf("> ");

        /* Read */
        fgets(cmdline, MAXARGS, stdin);
        if(feof(stdin)){
            exit(0);
        }

        /* Evaluate */
        eval(cmdline);
    }
}

/* Eval -- Evalute a command line */
void eval(char *cmdline){
    char *argv[MAXARGS];   // Argument list execve()
    char *environ;         // 环境变量列表environ暂设为空
    char buf[MAXARGS];     // Holds modified command line
    int bg;                // Should the job run in bg or fg?
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv); // 解析以空格为delimiter的命令, buf ---> argv
                               // bg = 1 ；后台执行
                               // bg = 0 ; 前台执行(shell挂起)
    if(argv[0] == NULL){
        return; // Ignore empty lines
    }

    if(!builtin_command(argv)){ // 不是内置命令
        if((pid = fork()) == 0){ // Child runs user job
            if(execve(argv[0], argv, environ) < 0){
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        /* parent waits for foreground job to terminate */
        if(!bg){ // bg = 0 ; 前台执行(shell挂起)
            int status;
            if(waitpid(pid, &status, 0) < 0){
                unix_error("waitfg: waitpid error");
            }
        }else{   // 后台执行，即父进程无需挂起，用SIGCHLD处理程序回收子进程
            if(signal(SIGCHLD, handler) == SIG_ERR){ // 设置SIGCHLD处理程序
                unix_error("signal error");
            }
            printf("%d %s", pid, cmdline);
        }
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv){
    if(!strcmp(argv[0], "quit")){ // quit command
        exit(0);
    }
    if(!strcmp(argv[0], "&")){ // Ignore singleton &
        return 1;
    }
    return 0; // not a builtin command
}

/* parseline -- Parse the command line and build the argv array */
int parseline(char *buf, char **argv){
    char *delim;  // Points to first spac delimiter
    int argc;
    int bg;

    buf[strlen(buf)-1] = ' '; // REplace trailing '\n' with space

    while(*buf && (*buf == ' ')){// Ignore leading spaces
        buf++;
    }

    /* Build the argv list */
    argc = 0;
    while((delim = strchr(buf, ' '))){
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim+1;
        while(*buf && (*buf == ' ')){ // Ignore spaces
            buf++;
        }
    }
    argv[argc] = NULL;

    if(argc == 0){ // Ignore bland line
        return 1;
    }

    /* should the job run in the background? */
    if((bg = (*argv[argc-1]) == '&') != 0){
        argv[--argc] = NULL;
    }

    return bg;
}
