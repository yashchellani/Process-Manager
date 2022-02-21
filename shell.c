#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define N 100
#define M 5

int main(){

    char *args[M];
    pid_t processes[N];
    bool killed[N];
    int n_process = 0;

    while (n_process < N){

        // tokenize user commands
        char *input = NULL;
        input = readline("cs205$ ");
        char *p = strtok(input, " ");
        char *cmd = p;
        int arg_cnt = 0;
        while (p = strtok(NULL, " ")){
            args[arg_cnt] = p;
            arg_cnt++;
        }

        if (strcmp(cmd, "run")==0){
            pid_t pid = fork();
            if (pid==0){
                char file[] = "./";
                strcat(file, args[0]);
                char* arg_array[] = {file, NULL, NULL, NULL, NULL};
                for (int i=1; i<arg_cnt; i++){
                    arg_array[i] = args[i];
                }
                execvp(arg_array[0], arg_array);
            }
            else if (pid>0){
                // parent process keep track of process states
                processes[n_process] = pid;
                killed[n_process] = 0;
                n_process++;
                printf("pid %d created\n", pid);
            }
        }
        else if (strcmp(cmd, "kill")==0){
            // check if pid exists and kill if found
            pid_t pid = atoi(args[0]);
            bool found = 0;
            for (int i=0; i<n_process; i++){
                if (processes[i]==pid){
                    found = 1;
                    //kill(pid, SIGTERM);
                    killed[i] = 1;
                    printf("%d killed\n", pid);
                    break;
                }
            }
            if (!found){
                printf("pid not found\n");
            }
        }
        else if (strcmp(cmd, "list")==0){
            // loop through all child processes, display status
            for (int i=0; i<n_process; i++){
                if (!killed[i]){
                    printf("%d created\n", processes[i]);
                }
                else {
                    printf("%d killed\n", processes[i]);
                }
            }

        }
        else if (strcmp(cmd, "exit")==0){
            break;
        }
        else {
            printf("invalid command\n");
        }

    }
    return 0;
}
