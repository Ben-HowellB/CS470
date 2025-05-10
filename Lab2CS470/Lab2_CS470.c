#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define NUM_CHILDREN 10

const char *commands[NUM_CHILDREN][4] = {
    {"echo", "Hello Benjamin", NULL},           // 0
    {"ls", "-l", NULL},                           // 1
    {"date", NULL},                               // 2
    {"whoami", NULL},                             // 3
    {"pwd", NULL},                                // 4
    {"uname", "-a", NULL},                        // 5
    {"echo", "Process 6", NULL},                  // 6
    {"echo", "Simulation is running", NULL},      // 7
    {"echo", "Another unique message", NULL},     // 8
    {"ps", NULL}                                  // 9
};

int main() {
    pid_t pids[NUM_CHILDREN];

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            printf("Child PID %d executing command: %s\n", getpid(), commands[i][0]);
            execvp(commands[i][0], (char *const *)commands[i]);
            // If execvp returns, an error occurred
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent stores child's PID
            pids[i] = pid;
        }
    }

    // Wait for all children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t child_pid = waitpid(pids[i], &status, 0);
        if (child_pid == -1) {
            perror("waitpid failed");
        } else {
            printf("Child PID %d terminated. ", child_pid);
            if (WIFEXITED(status)) {
                printf("Exited normally with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Terminated by signal %d\n", WTERMSIG(status));
            } else {
                printf("Terminated abnormally\n");
            }
        }
    }

    return 0;
}
