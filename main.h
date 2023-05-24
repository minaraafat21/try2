


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>





#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS MAX_COMMAND_LENGTH / 2 + 1

char *get_location(char *command);
int my_getline(char *word);
void sigint_handler();

