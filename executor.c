#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include "executor.h"
#include "redirect.h"

#define MAX_CMD 10
#define MAX_ARGS 10

void exec_commands(char **args[][10], int cmd_count, int background)
{
    int prev_fd = -1;
    for(int i=0;i<cmd_count;++i)
            {
                int fd[2];
                if(i<cmd_count-1)
                {
                    if(pipe(fd)==-1)
                    {
                        perror("Pipe creation failed");
                        exit(1);
                    }
                }
                int pid = fork();
                if(pid==0)
                {
                    if(prev_fd!=-1)
                    {
                        dup2(prev_fd,STDIN_FILENO);
                        close(prev_fd);
                    }
                    if(i<cmd_count-1)
                    {
                        dup2(fd[1],STDOUT_FILENO);
                        close(fd[0]);
                        close(fd[1]);
                    }
                    handle_redirection(args,&i);
                    signal(SIGINT,SIG_DFL);
                    signal(SIGTSTP, SIG_DFL);
                    execvp(args[i][0],args[i]);
                    perror("Execution Failed");
                    exit(1);
                }
                if(prev_fd!=-1)
                {
                    close(prev_fd);
                }
                if(i<cmd_count-1)
                {
                    close(fd[1]);
                    prev_fd = fd[0];
                }
            }
}