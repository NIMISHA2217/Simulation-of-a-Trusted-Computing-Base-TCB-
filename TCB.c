#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESSES 100

char trusted[MAX_PROCESSES][50];
int count = 0;

void writeLog(char process[], char status[])
{
    FILE *fp = fopen("execution.log", "a");

    time_t now;
    time(&now);

    fprintf(fp,
        "Time: %sProcess: %s | Status: %s\n",
        ctime(&now),
        process,
        status);

    fclose(fp);
}

void loadTrustedProcesses()
{
    FILE *fp = fopen("trusted.txt", "r");

    if(fp == NULL)
    {
        printf("trusted.txt not found\n");
        return;
    }

    count = 0;

    while(fscanf(fp, "%s", trusted[count]) != EOF)
    {
        count++;
    }

    fclose(fp);
}

int isTrusted(char process[])
{
    for(int i = 0; i < count; i++)
    {
        if(strcmp(process, trusted[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void executeProcess()
{
    char pname[50];

    printf("Enter Process Name: ");
    scanf("%s", pname);

    if(isTrusted(pname))
    {
        printf("\nExecution Allowed\n");

        writeLog(pname, "ALLOWED");
    }
    else
    {
        printf("\nExecution Denied\n");

        writeLog(pname, "DENIED");
    }
}

void addTrustedProcess()
{
    char pname[50];

    printf("Enter Process To Trust: ");
    scanf("%s", pname);

    FILE *fp = fopen("trusted.txt", "a");

    fprintf(fp, "\n%s", pname);

    fclose(fp);

    loadTrustedProcesses();

    printf("Trusted Process Added Successfully\n");

    writeLog(pname, "TRUSTED_LIST_MODIFIED");
}

void displayTrustedProcesses()
{
    printf("\nTrusted Processes\n");

    for(int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i+1, trusted[i]);
    }
}

int main()
{
    loadTrustedProcesses();

    int choice;

    while(1)
    {
        printf("\n===== TCB SYSTEM =====\n");
        printf("1. Execute Process\n");
        printf("2. Add Trusted Process\n");
        printf("3. View Trusted List\n");
        printf("4. Exit\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                executeProcess();
                break;

            case 2:
                addTrustedProcess();
                break;

            case 3:
                displayTrustedProcesses();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid Choice\n");
        }
    }
}
