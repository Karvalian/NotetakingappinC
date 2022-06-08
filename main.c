#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


void usage(char *progname, char *filename){
    printf("Usage : %s <data to add to %s> %s", progname, filename, filename);
    exit(-1);
}
void fatal(char *);
void *ec_malloc(unsigned int);

int main(int argc, char *argv[]){
    int fd;
    char *buffer, *datafile;
    buffer = ec_malloc(100);
    datafile = ec_malloc(20);
    strcpy(buffer, argv[1]);
    strcpy(datafile, argv[2]);
    printf("[DEBUG] buffer '%s' @ '%p'\n", buffer, buffer);
    printf("[DEBUG] datafile '%s' @ '%p'\n", datafile, datafile);
    if(argc<3)
        usage(argv[0], datafile);
    strncat(buffer, "\n", 1); 
    fd = open(datafile, O_WRONLY|O_APPEND|O_CREAT, S_IWUSR|S_IRUSR);
    printf("File descriptor is \'%d'\n", fd);
    if(fd==-1){
        fatal("in main() while opening the file");
    }
    if(write(fd, buffer, strlen(buffer))==-1)
        fatal("in main() while writing to the file");
    if(close(fd)==-1)
        fatal("in main() while closing the file");

    printf("Note(s) saved.");
    free(buffer);
    free(datafile);
}


void fatal(char *message){
    char error_message[100];
    strcpy(error_message, "[!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

void *ec_malloc(unsigned int size){
    void *ptr;
    ptr = malloc(size);
    if(ptr==NULL)
        fatal("in main() while allocating memory.");
    return ptr;
}
