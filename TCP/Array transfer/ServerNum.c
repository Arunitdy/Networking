//SERVER
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int min(int *arr1, int size) { 
	
	int min = 9999;
	for (int i = 0; i < size - 1; i++) {
		
		if( arr1[i] < min){

			min = arr1[i];
		}

	}
	return min ;

}
int max(int *arr1, int size) {
	
	int max = -9999;

	for (int i = 0; i < size - 1; i++) {
		
		if( arr1[i] > max){

			max = arr1[i];
		}

	}
	return max ;
}
int avg(int *arr1, int size) {
	
	int avg = 0;
	for (int i = 0; i < size - 1; i++) {
			avg += arr1[i];
		
	}
	return (avg/size);
}

int main(){
	
	struct sockaddr_in saddr, caddr;
	
	int SocketResponse = socket( AF_INET, SOCK_STREAM, 0 );
	
	if(SocketResponse == -1){
	
		printf(" error in socket creation \n");
	
	}else{
		printf("socket created :%d\n", SocketResponse);
		saddr.sin_family = AF_INET;
		saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		saddr.sin_port = htons(8888);
		
		if( bind( SocketResponse,( struct sockaddr* )&saddr,sizeof( saddr ) ) < 0){
			
			printf("error in bind \n");

		}else{

			printf("bind success \n");
			
			if( listen( SocketResponse, 5) < 0 ){

				printf("error in listen \n" );

			}else{
				printf("listen success \n");
				
				int clen = sizeof(caddr);

				
				int isock = accept(SocketResponse,(struct sockaddr*) &caddr,&clen);

				if( isock < 0){

					printf( "error in accept\n" );

				}else{

					printf("accepted\n");

					int arr[100], size;

					read(isock, &size, sizeof(size));
					read(isock, arr, sizeof(arr));
					
					
					printf(" array received: ");

		   			 for (int i = 0; i < size; i++) {

		   			     printf("%d ", arr[i]);

		   			 }

		   			printf("\n");

					int Min = min( arr,  size);
					write(isock, &Min, sizeof(Min));
					printf("send min: %d\n",Min);

					int Max = max(arr,  size);
					write(isock, &Max, sizeof(Max));
					printf("send max: %d\n",Max);

					int Avg = avg(arr,  size);
					write(isock, &Avg, sizeof(Avg));
					printf("send avg: %d\n",Avg);

					char ACK[10];
					read(isock, ACK, sizeof(ACK));
					printf("%s\n",ACK);

					
					char ACK2[]="Welcome";
					write(isock, ACK2 ,sizeof(ACK2));

					close(isock);
					close(SocketResponse);

				}
			}
		}
	}

}

