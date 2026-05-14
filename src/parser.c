#include <string.h>
#include "parser.h"

void parse_commands(char *cmds, char **args)
{
    int i=0;
    while(*cmds == ' ')
        cmds++;
    char *token = strtok(cmds," ");
    while(token!=NULL)
    {
        args[i++]=token;
        token=strtok(NULL," ");
    }
    args[i]=NULL;
}
void handle_pipes(char **commands, char *input, int *cmd_count)
{
    char *token = strtok(input, "|");
    while(token!=NULL)
    {
        commands[(*cmd_count)++] = token;
        token = strtok(NULL,"|");
    }
}