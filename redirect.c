#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "parser.h"

#define MAX_CMD 10
#define MAX_ARGS 10

void handle_redirection(char **args, int *i)
{
    for (int j = 0; j < MAX_ARGS && args[*i][j] != NULL; ++j)
    {
        if (strcmp(args[*i][j], ">>") == 0)
        {
            if (args[*i][j + 1] == NULL)
            {
                fprintf(stderr, "File Argument Missing.\n");
                exit(1);
            }
            int out = open(args[*i][j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (out < 0)
            {
                perror("File opening failed\n");
                exit(1);
            }
            dup2(out, STDOUT_FILENO);
            close(out);
            int k;
            for (k = j; args[*i][k + 2] != NULL; ++k)
            {
                args[*i][k] = args[*i][k + 2];
            }
            args[*i][k] = NULL;
            args[*i][k + 1] = NULL;
            j--;
        }

        else if (strcmp(args[*i][j], ">") == 0)
        {
            if (args[*i][j + 1] == NULL)
            {
                fprintf(stderr, "File Argument Missing\n");
                exit(1);
            }
            int out = open(args[*i][j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out < 0)
            {
                perror("File Open Failed\n");
                exit(1);
            }
            dup2(out, STDOUT_FILENO);
            close(out);
            int k;
            for (k = j; args[*i][k + 2] != NULL; ++k)
            {
                args[*i][k] = args[*i][k + 2];
            }
            args[*i][k] = NULL;
            args[*i][k + 1] = NULL;
            j--;
        }
        else if (strcmp(args[*i][j], "<") == 0)
        {
            if (args[*i][j + 1] == NULL)
            {
                fprintf(stderr, "File Argument Missing\n");
                exit(1);
            }
            int in = open(args[*i][j + 1], O_RDONLY);
            if (in < 0)
            {
                perror("File Open Failed\n");
                exit(1);
            }
            dup2(in, STDIN_FILENO);
            close(in);
            int k;
            for (k = j; args[*i][k + 2] != NULL; ++k)
            {
                args[*i][k] = args[*i][k + 2];
            }
            args[*i][k] = NULL;
            j--;
        }
        else if (strcmp(args[*i][j], "2>") == 0)
        {
            if (args[*i][j + 1] == NULL)
            {
                fprintf(stderr, "File Argument Missing\n");
                exit(1);
            }

            int err = open(args[*i][j + 1],
                           O_WRONLY | O_CREAT | O_TRUNC,
                           0644);

            if (err < 0)
            {
                perror("File Open Failed");
                exit(1);
            }

            dup2(err, STDERR_FILENO);

            close(err);

            int k;
            for (k = j; args[*i][k + 2] != NULL; ++k)
            {
                args[*i][k] = args[*i][k + 2];
            }

            args[*i][k] = NULL;

            j--;
        }
        else if (strcmp(args[*i][j], "2>>") == 0)
        {
            if (args[*i][j + 1] == NULL)
            {
                fprintf(stderr, "File Argument Missing\n");
                exit(1);
            }

            int err = open(args[*i][j + 1],
                           O_WRONLY | O_CREAT | O_APPEND,
                           0644);

            if (err < 0)
            {
                perror("File Open Failed");
                exit(1);
            }

            dup2(err, STDERR_FILENO);

            close(err);

            int k;
            for (k = j; args[*i][k + 2] != NULL; ++k)
            {
                args[*i][k] = args[*i][k + 2];
            }

            args[*i][k] = NULL;

            j--;
        }
        else if (strcmp(args[*i][j], "2>&1") == 0)
        {
            dup2(STDOUT_FILENO, STDERR_FILENO);

            int k;
            for (k = j; args[*i][k + 1] != NULL; ++k)
            {
                args[*i][k] = args[*i][k + 1];
            }

            args[*i][k] = NULL;

            j--;
        }
    }
}