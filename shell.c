    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <signal.h>
    #include "parser.h"
    #include "builtins.h"
    #include "executor.h"
    #include "config.h"
    #include "jobs.h"

    int main()
    {
        char input[INPUT_SIZE];
        handle_shell();

        while(1)
        {
            clear_cache();
            int background=0; 
            int input_status=0;
            char *commands[MAX_CMD];
            int cmd_count=0;
            char *args[MAX_CMD][MAX_ARGS];

            input_status = take_input(input);
            if(input_status)
                break;

            handle_pipes(commands,input,&cmd_count);

            for(int i=0;i<cmd_count;++i)
            {
                parse_commands(commands[i],args[i]);
            }   
            if(cmd_count==1 && handle_builtins(args))
            {
                continue;
            }
            background_process(args,cmd_count,&background);
            exec_commands(args,cmd_count,background);
            handle_wait(background,cmd_count);
        }
        return 0;
    }