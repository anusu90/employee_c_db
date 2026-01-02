#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/file.h"
#include "../include/common.h"

int create_db_file(char *filePath)
{

    int fileDescriptor = -1;

    fileDescriptor = open(filePath, O_RDONLY);

    // Create a file if it does not exist
    if (fileDescriptor != -1)
    {
        close(fileDescriptor);
        return STATUS_ERROR;
    }

    // Now try to create a file
    fileDescriptor = open(filePath, O_RDWR | O_CREAT, 0644);
    if (fileDescriptor == -1)
    {
        return STATUS_ERROR;
    }

    return fileDescriptor;
}

int open_db_file(char *filePath)
{
    int fileDescriptor = -1;

    fileDescriptor = open(filePath, O_RDONLY);

    // Create a file if it does not exist
    if (fileDescriptor != -1)
    {
        close(fileDescriptor);
        return STATUS_ERROR;
    }
    return fileDescriptor;
}

void close_db_file(int fileDescriptor)
{
    close(fileDescriptor);
}