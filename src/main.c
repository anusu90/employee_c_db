#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

void print_usage(char *argv[])
{

    printf("Usage: %s -n -f <file>\n", argv[0]);
    printf("Options:\n");
    printf("\t-n      Create a new file\n");
    printf("\t-f <file>  Specify the file to use\n");
}

int main(int argc, char *argv[])
{

    int flag;
    bool newFile = false;
    char *filePath = NULL;

    while ((flag = getopt(argc, argv, "nf:")) != -1)
    {
        switch (flag)
        {
        case 'n':
            newFile = true;
            break;
        case 'f':
            filePath = optarg;
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        default:
            printf("Hello world\n");
            return -1;
        }
    }

    if (filePath == NULL)
    {
        printf("No file path provided\n");
        print_usage(argv);
        return 1;
    }

    printf("New file: %d\n", newFile);
    printf("Filepath: %s\n", filePath);

    return 0;
}