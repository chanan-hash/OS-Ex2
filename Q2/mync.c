#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{


    if (argc != 3 || strcmp(argv[1], "-e") != 0)
    {
        printf("Usage: %s -e \"<program> <arguments>\"\n", argv[0]);
        return 1;
    }

// ./mync -e "ls -l"

    // Split the second argument into program name and arguments
    char *program = strtok(argv[2], " ");
    char *arguments = strtok(NULL, ""); // NULL to continue from the last position

    char *new_argv[] = {program, arguments, NULL};

    pid_t pid = fork(); // Create a new process

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0) // 
    {
        // Child process
        execvp(program, new_argv);

        // If execvp returns, there was an error
        perror("execvp");
        return 1;
    }
    else
    {
        // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish
    }

    return 0;
}