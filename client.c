#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
    //data section
    int fd;//server file descriptor
    int fd1;//client file descriptor
    char* client = "/tmp/client"; //client fifo filepath
    char* server = "/tmp/server"; //main fifo file path
    char client_name[80]; //buffer for client name
    //data section
    
    //read client name from user input, open server fifo, write client name to server fifo
    fgets(client_name,sizeof(client_name),stdin);
    fd = open(server,O_WRONLY); 
    write(fd,client_name,strlen(client_name) + 1);
    //make client fifo,open client fifo in read only
    mkfifo(client,0666); 
    fd1 = open(client, O_RDONLY);
    //get system call and send to server through client fifo (to be elaborated on later)
    char* dummy[80];
    fgets(dummy, sizeof(dummy),stdin);
    write(fd,dummy,strlen(dummy) + 1);
    //read back syscall info to print to the client
    char data_buffer[80];
    read(fd1,data_buffer,80);
    printf("%s\n",data_buffer);
    //close all fifos
    close(fd1);
    close(fd);




}