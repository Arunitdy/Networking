// SERVER

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
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

int main() {
    int socketResponse = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in saddr, caddr;

    if (socketResponse == -1) {
        printf("Error creating socket\n");
        return -1;
    }

    printf("Socket created: %d\n", socketResponse);

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(8888);

    // Bind'
    if (bind(socketResponse, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        printf("Error binding\n");
        return -1;
    }

    printf("Bind successful\n");

    if (listen(socketResponse, 5) < 0) {
        printf("Error listening\n");
        return -1;
    }

    printf("Listening for connections\n");

    int clen = sizeof(caddr);
    int isock = accept(socketResponse, (struct sockaddr *)&caddr, &clen);

    if (isock < 0) {
        printf("Error accepting connection\n");
        return -1;
    }

    printf("Connection accepted\n");

    int arr[100], size;

    // Receive size of the array
    read(isock, &size, sizeof(size));

    // Receive array elements
    read(isock, arr, sizeof(int) * size);

    printf("Received array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Sort the array
    sortArray(arr, size);

    // Send sorted array back
    write(isock, arr, sizeof(int) * size);

    printf("Sorted array sent back to client\n");

    close(isock);
    close(socketResponse);

    return 0;
}
