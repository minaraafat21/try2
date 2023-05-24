#include "main.h"

/**
 * get_location - get the location of exe file should excute
 * @command: the name of command
 * Return - the location of command
*/

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			file_path = malloc(1024);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}


void sigint_handler() {
    // Handle the SIGINT signal here
    // You can perform any necessary actions or cleanup
    // For example, you can terminate the program gracefully
}

/**
 * my_getline - get the command as input from console
 * @word: where the command save
 * Return: the length of input
 */

int my_getline(char *word)
{
	char buffer [1024];
	ssize_t num_bytes;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		return (1);
	}
	/* Read input from the user */
	if ((num_bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
	{
		buffer[num_bytes] = '\0';
        strcpy(word,buffer);
		return (num_bytes);
	}
	printf("\n");
	exit(EXIT_SUCCESS);
}
