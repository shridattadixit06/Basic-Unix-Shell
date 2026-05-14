#ifndef PARSER_H
#define PARSE_H

void parse_commands(char *cmds, char **args);
void handle_pipes(char **commands, char *input, int *cmd_count);

#endif