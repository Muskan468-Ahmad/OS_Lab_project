#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Function prototypes
void executeCommand(char *input);
void parseCommand(char *input, char **args);
int handleBuiltInCommands(char **args);
void executeWithRedirection(char **args);
void executeWithPiping(char *input);

int main() {
    char input[1024];

    while (1) {
        // Display prompt
        printf("mysh> ");
        fflush(stdout);

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nExiting...\n");
            break;
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        // Check for empty input
        if (strlen(input) == 0) continue;

        // Handle piping
        if (strchr(input, '|')) {
            executeWithPiping(input);
        } else {
            // Parse and execute command
            executeCommand(input);
        }
    }

    return 0;
}

void executeCommand(char *input) {
    char *args[100];
    pid_t pid;

    // Parse the command into arguments
    parseCommand(input, args);

    // Handle built-in commands like "cd" and "exit"
    if (handleBuiltInCommands(args)) return;

    // Handle redirection
    if (strchr(input, '>')) {
        executeWithRedirection(args);
        return;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Error: Fork failed");
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("Error: Command not found");
        }
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL);
    }
}

void parseCommand(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }
}

int handleBuiltInCommands(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting terminal...\n");
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "Error: No directory specified\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("Error");
            }
        }
        return 1;
    }
    return 0;
}

void executeWithRedirection(char **args) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            args[i] = NULL; // Split the command at '>'
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Error opening file");
                return;
            }
            dup2(fd, STDOUT_FILENO); // Redirect stdout
            close(fd);
            break;
        }
        i++;
    }

    if (execvp(args[0], args) == -1) {
        perror("Error: Command not found");
    }
    exit(EXIT_FAILURE);
}

void executeWithPiping(char *input) {
    char *commands[2];
    char *args1[100], *args2[100];
    int fd[2];

    commands[0] = strtok(input, "|");
    commands[1] = strtok(NULL, "|");

    pipe(fd);
    if (fork() == 0) {
        // First command
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        parseCommand(commands[0], args1);
        if (execvp(args1[0], args1) == -1) {
            perror("Error: Command not found");
        }
        exit(EXIT_FAILURE);
    }
    if (fork() == 0) {
        // Second command
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        parseCommand(commands[1], args2);
        if (execvp(args2[0], args2) == -1) {
            perror("Error: Command not found");
        }
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}    
