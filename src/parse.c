#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/parse.h"
#include "../include/common.h"

int create_db_header(db_header_t **headerOut)
{

    db_header_t *header = calloc(1, sizeof(db_header_t));

    if (header == NULL)
    {

        return STATUS_ERROR;
    }

    header->count = 0;
    header->filesize = sizeof(db_header_t);
    header->magic = HEADER_MAGIC;
    header->version = 0x1;

    *headerOut = header;

    return STATUS_SUCCESS;
}

int validate_db_header(int fileDescriptor, db_header_t **headerOut)
{
    if (fileDescriptor < 0)
    {
        printf("Got a bad FD from the user \n");
        return STATUS_ERROR;
    }

    db_header_t *header = calloc(1, sizeof(db_header_t));
    if (header == NULL)
    {
        printf("Error allocating memory for the header\n");
        return STATUS_ERROR;
    }

    if (read(fileDescriptor, header, sizeof(db_header_t)) != sizeof(db_header_t))
    {
        perror("Something went wrong");
        free(header);
        return STATUS_ERROR;
    }

    header->count = ntohs(header->count);
    header->filesize = ntohl(header->filesize);
    header->magic = ntohl(header->magic);
    header->version = ntohs(header->version);

    printf("version: %d\n", header->version);
    printf("magic: %d\n", header->magic);
    printf("filesize: %d\n", header->filesize);
    printf("count: %d\n", header->count);

    if (header->version != 0x1)
    {
        printf("Invalid version\n");
        free(header);
        return STATUS_ERROR;
    }

    if (header->magic != HEADER_MAGIC)
    {
        printf("Invalid magic number\n");
        free(header);
        return STATUS_ERROR;
    }

    struct stat dbStat = {0};
    fstat(fileDescriptor, &dbStat);

    if (dbStat.st_size != header->filesize)
    {
        printf("File size mismatch\n");
        free(header);
        return STATUS_ERROR;
    }

    *headerOut = header;
    return STATUS_SUCCESS;
}

int output_file(int fileDescriptor, db_header_t *header)
{

    if (fileDescriptor < 0)
    {
        printf("Got invalid file from the user\n");
        return STATUS_ERROR;
    }

    if (header == NULL)
    {
        printf("Got invalid header from the user\n");
        return STATUS_ERROR;
    }

    header->count = htons(header->count);
    header->filesize = htonl(header->filesize);
    header->magic = htonl(header->magic);
    header->version = htons(header->version);

    lseek(fileDescriptor, 0, SEEK_SET);

    if (write(fileDescriptor, header, sizeof(db_header_t)) != sizeof(db_header_t))
    {

        perror("Something went wrong");
        return STATUS_ERROR;
    }

    return STATUS_SUCCESS;
}