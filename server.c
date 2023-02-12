#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
    char name_buffer[80];//buffer for client name
    int fd; //file descriptor
    int fd1;

    char* server = "/tmp/server";//fifo filepath
    char* client = "/tmp/client"; //client specific fifo filepath

    mkfifo(server,0666);//create well-known fifo

    fd = open(server,O_RDONLY);//open fifo in read only
    read(fd,name_buffer,80);//read client name
    printf("%s\n",name_buffer); //print client name
    
    //close(fd); //close server
    fd1 = open(strcat(client,name_buffer), O_WRONLY);
    char data_buffer[80];
    read(fd,data_buffer,80);
    write(fd1,data_buffer,strlen(data_buffer) + 1);
    close(fd1);
    close(fd);

    
}