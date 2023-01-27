#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define EOF (-1)

struct scanning_s
{
    char    *input;
    long    size;
    long    pos;
}

struct extract_s
{
    struct scanning_s *input;
    int               len;
    char              *token;
}

void print_ps1(void)
{
    write(2, "$ ", 2);
}

void print_ps2(void)
{
    write(2, "> ", 2);
}


char *read_cmd(void)
{
    char    buf[1024];
    char    *ptr;
    char    ptrlen;
    int     buflen;
    char    *ptr2;

    ptr = NULL;
    ptrlen = 0;
    while (fgets(buf, 1024, stdin))
    {
        buflen = strlen(buf);
        if (!ptr)
            ptr = malloc(buflen + 1);
        else
        {
            ptr2 = realloc(ptr, ptrlen + buflen + 1);
            if (ptr2)
                ptr = ptr2;
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }
        if (!ptr)
        {
            fprintf(stderr, "error:failed to alloc buffer: %s\n", \
            strerror(errno));
            return (NULL);
        }
        strcpy(ptr + ptrlen, buf);//copy the data into ext. str
        if (buf[buflen - 1] == '\n')
        {
            //escaping the newline character
            if (buflen == 1 || buf[buflen - 2] != '\\')//double for one
                return (ptr);
            ptr[ptrlen + buflen - 2] = '\0';
            buflen -= 2;
            print_ps2();
        }
        ptrlen += buflen;
    }
    return (ptr);
}

/* Print a simple shell that prints a prompt string, reads input
and echoes the input back into the screen. */
int main(int ac, char **av)
{
    char *cmd;

    do
    {
        print_ps1();
        cmd = read_cmd();
        if (!cmd)
            exit(EXIT_SUCCESS);
        if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0) //if no input
        {
            free(cmd);
            continue;
        }
        if (strcmp(cmd, "exit\n") == 0)//input exit
        {
            free(cmd);
            break;
        }
        printf("%s\n", cmd);
        free(cmd);
    }   while(1);
    exit(EXIT_SUCCESS);
}
