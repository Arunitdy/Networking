#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int main(){
	int SocketResponse = socket( AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	
	if(SocketResponse < 0){
		printf("error in socket\n");
	}else{
		printf("socket created\n");
		
		client.sin_family = AF_INET;
		client.sin_addr.s_addr = inet_addr("127.0.0.1");
		client.sin_port = htons(8888);
		
		if(connect(SocketResponse , (struct sockaddr*)&client, sizeof(client) ) < 0){
			printf("error in connect\n");

		}else{

			printf("connected\n");
			
 			int arr[] = {5, 2, 9, 1, 6};
    			int size = sizeof(arr) / sizeof(arr[0]);
			
			
			write(SocketResponse, &size , sizeof(size));
			write(SocketResponse, arr, sizeof(arr));

   			printf("Array sent to server\n");
			
			
			int min,max,avg;

				
			read(SocketResponse, &min, sizeof(min));	
   			printf("min:%d ",min);

			read(SocketResponse, &max, sizeof(max));	
   			printf("max:%d ",max);

			read(SocketResponse, &avg, sizeof(avg));	

   			printf("avg:%d ",avg);
			
   			printf("\n");
			char ACK[]="Thank you";

			write(SocketResponse, ACK ,sizeof(ACK));
    			close(SocketResponse);

	
			char ACK2[30];
			read(SocketResponse, ACK2, sizeof(ACK2));
			printf("%s\n",ACK2);

			
			
		}
	}


}
