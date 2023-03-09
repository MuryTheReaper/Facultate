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

void deservire_client_suma_nr(int c) {
  // deservirea clientului
  int16_t a, b, suma;
  getInt(&a, c);
  getInt(&b, c);
  suma = a + b;
  sendInt(suma, c);
  close(c);
  // sfarsitul deservirii clientului;
}

void deservire_client_string(int c){

    char buffer[100];
    getString(buffer, c);

    printf("Am primit de la client: %s\n",buffer);

    for(int i=0;i<strlen(buffer);i++)
        if(buffer[i]>='a' && buffer[i]<='z'){
            buffer[i]-=32;
    }

    sendString(buffer, c);
    close(c);
}

void deservire_client_vector(int c){

    int16_t v[100], n;
    getVector(v, &n, c);

    for(int i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");

    for(int i=0;i<n;i++)
        v[i] = v[i] * v[i];

    sendVector(v, n, c);
    close(c);
}

void guessingGame(int c){
    
    srand(time(0));
    char *word = getString(word, c);
    printf("Word: %s\n",word);
    //randomP1 < randomP2 < randomP3 < strlen(word)
    int randomP1 = rand() % (strlen(word)/3);
    int randomP2 = rand() % (strlen(word)*2/3 - randomP1) + randomP1;
    if(randomP1 == randomP2)
        randomP2++;

    int randomP3 = rand() % (strlen(word) - randomP2) + randomP2;
    if(randomP2 == randomP3)
        randomP3++;


    int16_t guessSum;
    guessSum = word[randomP1] + word[randomP2] + word[randomP3];
    free(word);
    printf("P1: %d, P2: %d, P3: %d\n", randomP1, randomP2, randomP3);
    printf("Solution: %d\n", guessSum);

    char messageContinue[]="Wrong\nDo you want to continue?(y/n)";
    char messageWin[]="You win!";
    char messageStart[]="Start guessing!";

    sendString(messageStart, c);

    int16_t guess, tries = 1;

    while(tries < 6){

        getInt(&guess, c);
        printf("Guess: %d\n", guess);
        if(guess == guessSum){
            sendString(messageWin, c);
            sendInt(tries, c);
            break;
        }
        else{
            tries++;
            if(tries == 6){
                char messageLost[] = "You lost!";
                sendString(messageLost, c);
                break;
            }
            sendString(messageContinue, c);
            char *answer = getString(answer, c);
            if(strcmp(answer, "n") == 0){
                sendInt(tries, c);
                break;
            }

        }
    }

    printf("Game over!\n");
    close(c);

}

int main() {

  signal(SIGCHLD, SIG_IGN);
  int s;
  struct sockaddr_in server, client;
  int c, l;

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
  listen(s, 5);
  
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while (1) {
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    if (fork() == 0) { // fiu
      guessingGame(c);
      exit(0);
    }
    // se executa doar in parinte pentru ca fiul se termina mai sus din cauza exit-ului    
  }
}
