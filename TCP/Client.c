// Client

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>


int main(){

int socketResponse=socket(AF_INET,SOCK_STREAM,0);

struct sockaddr_in client;

if(socketResponse == -1){

printf("error");
}else{

printf("\n socket: %d\n",socketResponse);

client.sin_family = AF_INET;
client.sin_addr.s_addr = inet_addr("127.0.0.1");
client.sin_port = htons(8888);

if(connect(socketResponse,(struct sockaddr *)&client, sizeof(client)) < 0){

printf("error connect\n");

}else{

printf("connect %d\n",client.sin_port);
}


}


}