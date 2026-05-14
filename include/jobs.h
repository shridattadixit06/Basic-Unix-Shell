#ifndef JOBS_H
#define JOBS_H

void clear_cache();
void handle_shell();
int take_input(char *input, int size);
void handle_wait(int background, int cmd_count);
void background_process(char *args[][10],
                        int cmd_count,
                        int *background);

#endif