#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������
void print_help();
void execute_command(const char* command);

int main() 
{
    char input[256]; // ���ڴ洢�û����������

    // ��ӡ������Ϣ
    print_help();

    while (1) 
    {
        printf("> "); // ��ʾ��
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            // ȥ�����з�
            input[strcspn(input, "\n")] = '\0';

            // ����û����� "exit"���˳�����
            if (strcmp(input, "exit") == 0)
            {
                printf("Exiting...\n");
                break;
            }

            // ִ���û����������
            execute_command(input);
        }
        else
        {
            printf("Input error. Please try again.\n");
        }
    }

    return 0;
}

// ��ӡ������Ϣ
void print_help() 
{
    printf("Supported commands:\n");
    printf("  cp <source> <destination>                      - Copy a file\n");
    printf("  rm <file>                                      - Delete a file\n");
    printf("  tar -czf <archive.tar.gz> <file1> <file2> ...  - Compress files\n");
    printf("  tar -xzf <archive.tar.gz>                      - Extract files\n");
    printf("  exit                                           - Exit the program\n");
    printf("Enter a command:\n");
}

// ִ���û����������
void execute_command(const char* command) 
{
    char cmd[256]; // ���ڴ洢����������
    char operation[16]; // ���ڴ洢�������ͣ�cp, rm, tar��
    char arg1[128], arg2[128]; // ���ڴ洢����

    // ��������
    if (sscanf(command, "%s %s %s", operation, arg1, arg2) >= 2)
    {
        if (strcmp(operation, "cp") == 0)
        {
            // �ļ�����
            snprintf(cmd, sizeof(cmd), "cp %s %s", arg1, arg2);
            printf("Executing: %s\n", cmd);
            system(cmd);
        }
        else if (strcmp(operation, "rm") == 0) 
        {
            // �ļ�ɾ��
            if (strcmp(arg1, "-rf") == 0)
            {
                snprintf(cmd, sizeof(cmd), "rm -rf %s", arg2);
                printf("Executing: %s\n", cmd);
                system(cmd);
            }
            else
            {
                snprintf(cmd, sizeof(cmd), "rm %s", arg1);
                printf("Executing: %s\n", cmd);
                system(cmd);
            }
        }
        else if (strcmp(operation, "tar") == 0) 
        {
            if (strcmp(arg1, "-czf") == 0) 
            {
                // �ļ�ѹ��
                snprintf(cmd, sizeof(cmd), "tar -czf %s %s", arg2, command + strlen("tar -czf ") + strlen(arg2) + 1);
                printf("Executing: %s\n", cmd);
                system(cmd);
            }
            else if (strcmp(arg1, "-xzf") == 0)
            {
                // �ļ���ѹ
                snprintf(cmd, sizeof(cmd), "tar -xzf %s", arg2);
                printf("Executing: %s\n", cmd);
                system(cmd);
            }
            else
            {
                printf("Invalid tar command. Use -czf for compression or -xzf for extraction.\n");
            }
        }
        else 
        {
            printf("Unknown command: %s\n", operation);
        }
    }
    else 
    {
        printf("Invalid command format. Please check the help message.\n");
    }
}