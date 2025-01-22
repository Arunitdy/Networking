//SERVER
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


void sortArray(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
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
					
					printf("%d",size);
					printf(" array received: ");

		   			 for (int i = 0; i < size; i++) {

		   			     printf("%d ", arr[i]);

		   			 }
		   			 printf("\n");

					sortArray(arr, size);
					write(isock, arr, sizeof(arr));
					
					char ACK[10];
					if(read(isock, ACK, sizeof(ACK)) > 0){
					
					
						printf("%s\n",ACK);

					
						char ACK2[]="Welcome";
						write(isock, ACK2, sizeof(ACK2));
					

					}

					close(isock);
					close(SocketResponse);

				}
			}
		}
	}

}

