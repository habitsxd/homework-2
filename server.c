#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
    //data section
    char name_buffer[80];//buffer for client name
    int fd; //file descriptor for server fifo
    int fd1;//file descriptor for client fifo
    char* server = "/tmp/server";//fifo filepath
    char* client = "/tmp/client"; //client specific fifo filepath
    //data section

    //create server fifo
    mkfifo(server,0666);
    //open server fifo in read only, read client name, print client name on the server
    fd = open(server,O_RDONLY);
    read(fd,name_buffer,80);
    printf("%s\n",name_buffer); 
    //maintenence - close old server fifo, open new instance
    close(fd);
    fd = open(server,O_RDONLY); 
    //read in client request from server fifo to a data buffer
    char data_buffer[80];
    read(fd,data_buffer,80);
    //open client server and write to it
    fd1 = open(client, O_WRONLY);
    write(fd1,data_buffer,strlen(data_buffer) + 1);
    //close both fifos
    close(fd1);
    close(fd);

    
}