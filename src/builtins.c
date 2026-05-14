#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtins.h"

int handle_builtins(char **args)
{
    if(args[0] == NULL)
        return 0;
    if(strcmp(args[0], "cd")==0)
            {
                if(args[1]==NULL)
                {
                    char *home = getenv("HOME");
                    if(home==NULL)
                    {
                        fprintf(stderr,"HOME not set\n");
                    }
                    if(home!=NULL)
                    {
                        if(chdir(home)!=0)
                        {
                            perror("cd failed");
                        }
                    }
                }
                else
                {
                    if(chdir(args[1]) != 0)
                    {
                            perror("cd failed");
                        }
                }
                return 1;
            }
    return 0;
}