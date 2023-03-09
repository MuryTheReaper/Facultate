#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>


#define BUFLEN 512
#define PORT 1234

int sumFromString(char c[]){

    int s=0;

    for(int i=0;i<strlen(c);i++){
        if(c[i]>='0' && c[i]<='9'){

            int n = c[i]-'0';
            if(n%2 == 1)
                s+=n;

        }
    }

    return s;
}

int main(int argc,const char* argv[]){

    int s;
    struct sockaddr_in server,client;
    int c,l;

    s=socket(AF_INET,SOCK_DGRAM,0);
    if(s<0){
         printf("Eroare la crearea socketului server\n");
         return 1;
    }

    int port;
    port=atoi(argv[2]);
    printf("Port %d\n", port);
    printf("Ip %s\n", argv[1]);

    memset(&server,0,sizeof(server));
    server.sin_port=htons(port);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(argv[1]);


    if(bind(s,(struct sockaddr *)&server,sizeof(server))<0)         {
          printf("Eroare la bind\n");
          return 1;
    }

    l=sizeof(client);
    memset(&client,0,sizeof(client));


    char numbers[BUFLEN];
    memset(numbers, 0, BUFLEN);
    int max = 0, nr = 0;
    while(1){
        //recvfrom(s,&buf,BUFLEN,0,(struct sockaddr *)&client,&l);
        //sendto(s,&buf,BUFLEN,0,(struct sockaddr *)&client,l);

        recvfrom(s, &numbers, BUFLEN, 0, (struct sockaddr *) &client, &l);
        nr++;
        printf("Numbers: %s\n", numbers);
        int sum = sumFromString(numbers);
        printf("Sum : %d\n", sum);
        int newPort = port + sum;

        if(newPort > max)
            max = newPort;

        int nS = socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in newServer;
        memset(&newServer,0,sizeof(newServer));
        newServer.sin_port=htons(newPort);
        newServer.sin_family=AF_INET;
        newServer.sin_addr.s_addr=inet_addr(argv[1]);

        bind(nS,(struct sockaddr *)&newServer,sizeof(newServer));


        char buf[BUFLEN];
        sprintf(buf, "%d", nr);
        sendto(nS,&buf,BUFLEN,0,(struct sockaddr *)&client,l);

        sprintf(buf, "%d", max);
        sendto(nS,&buf,BUFLEN,0,(struct sockaddr *)&client,l);

        close(nS);


    }

    close(s);
}


