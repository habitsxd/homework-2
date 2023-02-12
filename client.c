#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
    int fd;//server file descriptor
    int fd1;//client file descriptor
    char* client = "/tmp/client"; //client fifo filepath
    char* server = "/tmp/server"; //main fifo file path

    char client_name[80]; //buffer for client name

    fgets(client_name,sizeof(client_name),stdin); //read in client name from user
    fd = open(server,O_WRONLY); //open main fifo to pass client name
    write(fd,client_name,strlen(client_name) + 1); //write the client name to the fifo

    //close(fd); //close main fifo
    char* client_full_path = strcat(client,client_name);
    mkfifo(client_full_path,0666); //make client specific fifo
    fd1 = open(client_full_path, O_RDONLY);//open client fifo as for reading
    char* dummy = "dummy";
    write(fd,dummy,strlen(dummy));
    char data_buffer[80];

    read(fd1,data_buffer,80);
    close(fd1);
    close(fd);




}