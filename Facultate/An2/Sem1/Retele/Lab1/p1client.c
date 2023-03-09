#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>



int main(){

    int clientSocket,n, nr, rez;
    struct sockaddr_in serverAddr;


    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = 8888;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof serverAddr);

    printf("Introduceti nr de numere\n");
    scanf("%d", &n);
    
    send(clientSocket, &n, sizeof(int),0);
    for(int i=0;i<n;i++){
        scanf("%d", &nr);
        send(clientSocket, &nr, sizeof(int),0);
    }

    recv(clientSocket, &rez, sizeof(int),0);
    printf("Rezultat: %d\n", rez);

    close(clientSocket);



}
