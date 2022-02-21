#include<stdio.h>
//#include<limits.h>
#define MAX 100
#define N 20
#define M 5

// denotes where the last item in priority queue is
// initialized to -1 since no item is in queue
int idx = -1;

// pqVal holds data for each index item
// pqPriority holds priority for each index item
int pqVal[MAX];
int pqPriority[MAX];

int isEmpty(){
    return idx == -1;
}

int isFull(){
    return idx == MAX - 1;
}
// Insert the element in maintaining items in sorted order 
// of their priority
void enqueue(int data, int priority)
{
    if(!isFull()){
        // first item being entered
        if(idx == -1){
            idx++; // increase the index
            pqVal[idx] = data;
            pqPriority[idx] = priority;
            return;
        }
        else{
             // Increase the index
            idx++;
            // in reverse order
            for(int i = idx-1; i >= 0;i--){
                // shift all items rightwards with higher priority
                // than the element we trying to insert
                if(pqPriority[i] >= priority){
                    pqVal[i+1] = pqVal[i];
                    pqPriority[i+1] = pqPriority[i];
                }
                else{
                    // insert item just before where
                    // lower priority index was found
                    pqVal[i+1] = data;
                    pqPriority[i+1] = priority;
                    break;
                }
                
            }
        }

    }
}

// returns item with highest priority
// note highest priority in max priority queue is last item in array
int peek()
{
    return idx;
}

// just reducing index would mean we have dequed
// the value would be sitll there but we can say that 
// no more than a garbage value
void dequeue()
{
        idx--;
}
void display(){
    for (int i = 0; i <= idx; i++) {
        printf("(%d, %d)\n",pqVal[i], pqPriority[i]);
    } 
}

int addToQueue{

    return 0;
}
// Driver Code
int main()
{
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
    // To enqueue items as per priority
    enqueue(25, 1);
    enqueue(10, 10);
    enqueue(15, 50);
    enqueue(20, 100);
    enqueue(30, 5);
    enqueue(40, 7);
    
    printf("Before Dequeue : \n");
    display();
 
    // // Dequeue the top element
    dequeue(); // 20 dequeued
    dequeue(); // 15 dequeued
    
    printf("\nAfter Dequeue : \n");
    display();

    return 0;
}