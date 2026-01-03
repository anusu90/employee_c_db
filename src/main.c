#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "../include/file.h"
#include "../include/common.h"
#include "../include/parse.h"

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
    int fileDescriptor = -1;
    db_header_t *header = NULL;

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

    if (newFile)
    {
        fileDescriptor = create_db_file(filePath);
        if (fileDescriptor == STATUS_ERROR)
        {
            printf("Error creating database file. File may already exist.\n");
            return -1;
        }

        if (create_db_header(&header) == STATUS_ERROR)
        {
            printf("Error creating database header\n");
            return -1;
        }

        if (output_file(fileDescriptor, header) == STATUS_ERROR)
        {
            printf("Error writing database header\n");
            return -1;
        }
    }
    else
    {
        fileDescriptor = open_db_file(filePath);
        if (fileDescriptor == STATUS_ERROR)
        {
            printf("Error opening database file. File may not exist.\n");
            return 1;
        }

        if (validate_db_header(fileDescriptor, &header) == STATUS_ERROR)
        {
            printf("Error validating database header\n");
            return -1;
        }
    }

    if (fileDescriptor == -1)
    {
        printf("Error opening database file\n");
        return 1;
    }

    printf("Database file opened successfully\n");

    close_db_file(fileDescriptor);

    return 0;
}