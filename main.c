
void print_ps1(void)
{
    fprintf(stderr, "$ ");
}

/*void print_ps2(void)
{
    fprintf(stderr, "> ");
}*/


char *read_cmd(void)
{
    char    buf[1024];
    char    *ptr;
    char    ptrlen;
    int     buflen;
    char    *ptr2;

    while (fgets(buf, 1024, stdin))//read about fgets
    {
        buflen = strlen(buf);
        if (!ptr)//first entry
            ptr = malloc(buflen+1);
        else//other entry
        {
            ptr2 = realloc(ptr, ptrlen+buflen+1);
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
        strcpy(ptr+ptrlen, buf);//copy the data into ext. str
        if (buf[buflen - 1] == '\n')
        {
            //escaping the newline character
            if (buflen == 1 || buf[buflen - 2] != '\\')//double for one
                return (ptr);
            ptr[ptrlen+buflen - 2] = '\0';
            buflen -= 2;
            print_ps2();
        }
        ptrlen += buflen;
    }
    return (ptr);
}

int main(int ac, char **av)
{

    char *cmd;

    while (1)
    {
        print_ps1();//PRINT FIRST PROMPT STRING (SHELL WAIT COMMAND)
        //print_ps2();//PRINT SECOND PROMPT STRING FOR MULTILINE CMD
        cmd = read_cmd();//Read the next line of an input
        if (!cmd)
            exit(EXIT_SUCCESS);//why
        if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)//if no input
        {
            free(cmd);
            continue;
        }
        if (strcmp(cmd, "exit\n") == 0)//we quit the shell on exit_cm
        {
            free(cmd);
            break;
        }
        printf("s\n", cmd);
        free(cmd);
    }
    exit(EXIT_SUCCESS);
}
