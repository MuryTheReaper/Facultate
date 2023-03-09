/* Enunt: Un server primeste numere de la clienti si le afiseaza pe ecran. Serverul trimite inapoi fiecarui client dublul numarului.

Compilare: 
	gcc server.c -o server
	gcc client.c -o client
	
Rulare in doua terminale diferite:
	./server
	./client
*/
	
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, int **argv){
  int clientSocket;
  char numar[10], rez[10];
  struct sockaddr_in serverAddr;

  char buffer[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &serverAddr.sin_addr, buffer, sizeof(buffer));
  printf("AF_INET: %s\n", buffer);

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);				/* Create the socket. The three arguments are:  1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  if(clientSocket < 0){
    printf("Eroare la creare socket\n");
    return 1;
  }
  serverAddr.sin_family = AF_INET;						/* Address family = Internet */
  serverAddr.sin_port = 8899;							/* Set port number*/
  serverAddr.sin_addr.s_addr = inet_addr("172.30.112.225");				/* Set IP address to localhost */
  if(connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof serverAddr)<0){
    printf("Eraore la conectare\n");
    return 1;
  }
  printf("Introduceti numarul vostru:\n");
  fgets(numar,10,stdin);
  printf("Trimit la server %s\n",numar); 

  send(clientSocket,&numar,sizeof(char)*strlen(numar),0);

  recv(clientSocket, &rez, sizeof(char)*strlen(rez), 0);						/* Read the message from the server into the buffer */

  printf("Data received: %s\n",rez);   					/* Print the received message */

  close(clientSocket);

  return 0;
}
