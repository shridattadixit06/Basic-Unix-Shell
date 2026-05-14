#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "jobs.h"
#include "config.h"
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

void clear_cache()
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}
void handle_shell()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
int take_input(char *input, int size)
{
    printf(">");
    if (fgets(input, size, stdin) == NULL)
        return 1;
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) == 0)
        return 0;
    if (strcmp(input, "exit") == 0)
        return 1;
    return 2;
}
void handle_wait(int background, int cmd_count)
{
    if (!background)
    {
        for (int i = 0; i < cmd_count; ++i)
        {
            wait(NULL);
        }
    }
}
void background_process(char *args[][MAX_ARGS],
                        int cmd_count,
                        int *background)
{
    for (int j = 0; args[cmd_count - 1][j] != NULL; ++j)
    {
        if (strcmp(args[cmd_count - 1][j], "&") == 0)
        {
            *background = 1;
            args[cmd_count - 1][j] = NULL;
            break;
        }
    }
}