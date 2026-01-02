#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int flag;
    bool newFile = false;
    char *filepath = NULL;

    while ((flag = getopt(argc, argv, "nf:")) != -1)
    {
        switch (flag)
        {
        case 'n':
            newFile = true;
            break;
        case 'f':
            filepath = optarg;
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        default:
            printf("Hello world\n");
            return -1;
        }
    }

    printf("New file: %d\n", newFile);
    printf("Filepath: %s\n", filepath);

    return 0;
}