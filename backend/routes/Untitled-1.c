
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
void history_file(char *cmd)
{
    FILE *fp = fopen("command_history.txt", "a");
    if (fp == NULL)
    {
        printf("...Error...");
        exit(1);
    }
    fprintf(fp, "%s", cmd);
    fclose(fp);
}
void ls()
{
    struct dirent *de;
    DIR *dr = opendir(".");
    if (dr == NULL)
    {
        printf("\n...error finding directory...\n");
        exit(0);
    }
    printf("\n");
    while ((de = readdir(dr)) != NULL)
        printf("%s\t", de->d_name);
    closedir(dr);
    printf("\n");
}
void ls_l()
{
    int pid = fork();
    if (pid < 0)
    {
        printf("\n...error...\n");
        exit(-1);
    }
    else if (pid == 0)
        execlp("/bin/ls", "ls", "-l", NULL);
    else
        wait(NULL);
}
void makedir(char *cmd)
{
    int len = strlen(cmd);
    char *p = (char *)calloc(50, sizeof(char));
    for (int i = 0; i <= 5; i++)
        cmd++;
    strncpy(p, cmd, len - 7);
    if (mkdir(p, 0777) == -1)
        printf("\n...your command is invalid...\n");
    else
        printf("\nyour directory named \"%s\" has been created\n", p);
    p = NULL;
}
void cd(char *cmd)
{
    int len = strlen(cmd);
    char *p = (char *)calloc(50, sizeof(char));
    for (int i = 0; i <= 2; i++)
        cmd++;
    strncpy(p, cmd, len - 4);
    if (chdir(p) == -1)
        printf("\n...your command is invalid...\n");
    p = NULL;
}
void removedir(char *cmd)
{
    int len = strlen(cmd);
    char *p = (char *)calloc(50, sizeof(char));
    for (int i = 0; i <= 5; i++)
        cmd++;
    strncpy(p, cmd, len - 7);
    if (rmdir(p) == -1)
        printf("\n...your command is invalid...\n");
    else
        printf("\ndirectory named \"%s\" has been deleted\n", p);
    p = NULL;
}
void clear()
{
    system("clear");
}
void quit()
{
    exit(0);
}
void env(char *en[])
{
    int i = 0;
    printf("\n");
    while (en[i] != NULL)
    {
        printf("%s", en[i]);
        i++;
    }
    printf("\n");
}
void pwd()
{
    char buffer[19075];
    getcwd(buffer, 19075);
    printf("\nThe present wroking directory is :- %s\n", buffer);
}
void history(char *cmd)
{
    FILE *fp = fopen("command_history.txt", "r");
    if (fp == NULL)
    {
        printf("\n...Error...\n");
        exit(1);
    }
    else
    {
        char history[75];
        int count = 0;
        printf("\n");
        while (fgets(history, 75, fp))
        {
            printf("%d %s", ++count, history);
            if (history[strlen(history) - 1] != '\n')
                printf("\n");
        }
        fclose(fp);
    }
}
void parse(char *cmd)
{
    if (strncmp(cmd, "ls", strlen(cmd) - 1) == 0)
        ls();
    else if (strncmp(cmd, "ls -l", strlen(cmd) - 1) == 0)
        ls_l();
    else if (strncmp(cmd, "clear", 5) == 0)
        clear();
    else if (strncmp(cmd, "quit", 3) == 0)
        quit();
    else if (strncmp(cmd, "mkdir", 5) == 0)
        makedir(cmd);
    else if (strncmp(cmd, "cd", 2) == 0)
        cd(cmd);
    else if (strncmp(cmd, "rmdir", 5) == 0)
        removedir(cmd);
    else if (strncmp(cmd, "pwd", 3) == 0)
        pwd();
    else if (strncmp(cmd, "history", 7) == 0)
        history(cmd);
    else
        printf("\n...your command is invalid...\n");
}
int main(int argc, char *argv[], char *envp[])
{
    char buff[FILENAME_MAX], *cmd;
    cmd = (char *)calloc(75, sizeof(char));
    while (1)
    {
        getcwd(buff, FILENAME_MAX);
        printf("%s>", buff);
        fgets(cmd, 75, stdin);
        history_file(cmd);
        if (strncmp(cmd, "env", 3) == 0)
            env(envp);
        else
            parse(cmd);
    }
    return 0;
}
