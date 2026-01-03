#ifndef PARSE_H
#define PARSE_H

#define HEADER_MAGIC 0x4c4c4144

typedef struct
{
    unsigned short count;
    unsigned int filesize;
    unsigned int magic;
    unsigned short version;
} db_header_t;

int create_db_header(db_header_t **header);
int validate_db_header(int fileDescriptor, db_header_t **header);
int output_file(int fileDescriptor, db_header_t *header);

#endif