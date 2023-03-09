/* Serverul va returna clientului suma numerelor primite. */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){

    int welcomeSocket, newSocket, n, rez, nr;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = 8888;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    listen(welcomeSocket, 3);

    addr_size = sizeof serverStorage;

    while(1){
        
        newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
        
        printf("Client-ul s-a connectat... \n");

        recv(newSocket, &n, sizeof(int), 0);
        
        printf("Am primit %d numere\n",n);

        rez=0;
        for(int i=0; i<n; i++){
            recv(newSocket, &nr, sizeof(int), 0);
            rez+=nr;
        }

        send(newSocket, &rez, sizeof(int), 0);

        close(newSocket);
    }
    close(welcomeSocket);


}
