

#include "main.h"

int main(int ac, char **arg, char **envp)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    char buffer[1024];
    pid_t pid;
    int status;

    while (1)
    {
        // Print prompt
        printf("$ ");
        fflush(stdout);


        char *command ;
        ssize_t num_bytes;

        if (signal(SIGINT, sigint_handler) == SIG_ERR)
        {
            return (1);
        }
        /* Read input from the user */
        if ((num_bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
        {
            buffer[num_bytes] = '\0';
        }
        command = buffer;
        printf("\n");

        // Remove newline character from end of string
        char *newline = strchr(command, '\n');
        if (newline != NULL)
        {
            *newline = '\0';
        }

        // Parse command into arguments
        char *token = strtok(command, " ");
        int num_args = 0;

        while (token != NULL)
        {
            // Ignore comments
            if (token[0] == '#')
            {
                token = NULL;
                break;
            }

            // Store argument and update counter
            args[num_args++] = token;

            // Get next token
            token = strtok(NULL, " ");
        }
        args[num_args] = NULL;
        // Execute command
        if (num_args > 0)
        {
            // Get path to executable file
            char *path = get_location(args[0]);
            if (path == NULL)
            {
                printf("%s: command not found\n", args[0]);
            }
            else
            {
                pid = fork();

                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                    // Child process
                    int ret = execve(path, args, envp);
                    if (ret == -1)
                    {
                        perror("execve");
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    // Parent process
                    waitpid(pid, &status, 0);
                }

                // Free memory allocated for path
                // free(path);
            }
        }
    }

    return 0;
}