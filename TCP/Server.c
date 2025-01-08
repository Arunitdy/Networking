
//SERVER

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(){

    int socketResponse=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in saddr,caddr;


    if(socketResponse == -1){

        printf("error socket");

    }else{
        printf("\n socket: %d\n",socketResponse);

        saddr.sin_family = AF_INET;
        saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        saddr.sin_port = htons(8888);
        //bind
        if(bind(socketResponse,(struct sockaddr*)&saddr,sizeof(saddr)) < 0){

            printf("error in bind\n");

        }else{
            
            printf("bind\n");

            if(listen(socketResponse,5) < 0){

                printf("error listen\n");

            }else{

                printf("listening \n");
                //accept
                int clen=sizeof(caddr);

                int isock = accept(socketResponse,(struct sockaddr*) &caddr,&clen);

                if(isock < 0){

                    printf("error acceping\n");

                }else{

                    printf("accepted  \n port: %d\n",saddr.sin_port);

                }

            }
        }
    }


}