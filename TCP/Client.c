
// CLIENT

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int socketResponse = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in client;

    if (socketResponse == -1) {
        printf("Error creating socket\n");
        return -1;
    }

    printf("Socket created: %d\n", socketResponse);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(8888);

    if (connect(socketResponse, (struct sockaddr *)&client, sizeof(client)) < 0) {
        printf("Error connecting\n");
        return -1;
    }

    printf("Connected to server\n");

    int arr[] = {5, 2, 9, 1, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Send size of the array
    write(socketResponse, &size, sizeof(size));

    // Send array elements
    write(socketResponse, arr, sizeof(int) * size);

    printf("Array sent to server\n");

    // Receive sorted array
    read(socketResponse, arr, sizeof(int) * size);

    printf("Sorted array received: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    close(socketResponse);

    return 0;
}
