#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>


void sendInt(int16_t nr, int c){

    nr = htons(nr);
    send(c, &nr, sizeof(nr), 0);
}

void getInt(int16_t *nr, int c){

    recv(c, nr, sizeof(*nr), MSG_WAITALL);
    *nr = ntohs(*nr);

}

char* getString(char *str, int c){

    int16_t len;
    recv(c, &len, sizeof(len),MSG_WAITALL);
    len = ntohs(len);
    str = (char *)malloc(len);
    recv(c, str, len, MSG_WAITALL);
    str[len] = '\0';

    return str;

}

void sendString(char *str, int c){

    int16_t len = strlen(str);
    len = htons(len);
    send(c, &len, sizeof(int16_t), 0);
    send(c, str, strlen(str), 0);
}

void sendStringNumber(char *str, int c){

   sendInt(strlen(str), c);
   for(int i = 0; i < strlen(str); i++){
        sendInt((int)str[i], c);
   }
}

void getVector(int16_t *v, int16_t* n, int c){

    getInt(n, c);
    recv(c, v, *n * sizeof(int16_t), MSG_WAITALL);
    for(int i = 0; i < *n; i++)
        v[i] = ntohs(v[i]);

}

void sendVector(int16_t *v, int16_t n, int c){

    sendInt(n, c);
    for(int i = 0; i < n; i++)
        v[i] = htons(v[i]);
    send(c, v, n * sizeof(int16_t), 0);

}

int checkLetterInWord(char* letter, char* word){

    if(strstr(word,letter)==NULL)
        return -1;
    return 1;
}

void miniGame(int n, int c1, int c2){

    printf("Start\n");

    sendInt(n, c1);
    sendInt(n, c2);

    srand(time(0));

    char randomLetter[2];
    char *word1, *letter1, *wordAux;
    char *word2, *letter2;
    randomLetter[0] = (char) (rand()%26+97);
    letter1 = randomLetter;

    printf("%s\n",randomLetter);

    while(1){
        sendString(letter1, c1);

        word1 = getString(word1,c1);
        letter1 = getString(letter1, c1);

        printf("%s %s\n",word1,letter1);

        sendString(word1, c1);

        int status = checkLetterInWord(word1,letter2);
        sendInt(status, c1);

        sendString(letter1,c2);
        word2 = getString(word2,c2);
        letter2 = getString(letter2,c2);
        sendString(word1,c2);

        status = checkLetterInWord(word2,letter1);
        sendInt(status, c2);

        letter1 = letter2;

        printf("%s %s\n",word2,letter2);

        printf("Finished while\n");
        if(status == -1)
            break;

    }


    free(word1);
    free(word2);
    free(letter1);
    free(letter2);
    close(c1);
    close(c2);


}

int main() {

  signal(SIGCHLD, SIG_IGN);
  int s;
  struct sockaddr_in server, client1, client2;
  int c1,c2, l1, l2, n = 1;

  /* Create the socket.
  The three arguments are:
  1) Internet domain 2) Stream socket
  3) Default protocol (TCP in this case) */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234); /* Set port number*/
  server.sin_family = AF_INET;  /* Address family = Internet */
  server.sin_addr.s_addr = inet_addr("127.0.0.1"); /* Set IP address to localhost */

  /* Bind the address struct to the socket */
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

 /* Listen on the socket, with 5 max connection requests queued */
  listen(s, 6);
  
  l1 = sizeof(client1);
  memset(&client1, 0, sizeof(client1));
  l2 = sizeof(client2);
  memset(&client2, 0, sizeof(client2));
  
  while (1) {
    c1 = accept(s, (struct sockaddr *) &client1, &l1);
    c2 = accept(s, (struct sockaddr *) &client2, &l2);

    printf("S-au conectat clientii.\n");
    if (fork() == 0) {
      miniGame(n, c1,c2);
      exit(0);
    }
    n++;
  }
}
