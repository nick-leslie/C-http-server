#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include "http.h"
int main(int argc,char* argv[]) {
    if(argc < 2) {
        printf("please add in the port number\n");
        return 1;
    }
    getRoutes* routes = constructRoutesStruct("./");

    int soc, newSoc;
    char* buffer = malloc(sizeof(char) * 512);
    char *sendBuffer = NULL;

    soc = socket(AF_INET,SOCK_STREAM,0);
    if(soc < 0) {
        perror("Error creating socket");
        return 1;
    }
    struct sockaddr_in sockAddrDat = {};
    struct sockaddr_in their_addr;
    sockAddrDat.sin_family = AF_INET;
    int port = atoi(argv[1]);
    sockAddrDat.sin_port = htons(port);
    sockAddrDat.sin_addr.s_addr = INADDR_ANY;
    int bindErr = bind(soc,(struct sockaddr*)&sockAddrDat,sizeof(sockAddrDat));
    if(bindErr != 0) {
        perror("Error binding");
        return 1;
    }
    listen(soc,5);
    printf("entering the main loop\n");
    while (1) {
        socklen_t addr_len = sizeof(their_addr);
        newSoc = accept(soc, (struct sockaddr *)&their_addr,&addr_len );
	printf("got client\n");
        if(newSoc < 0) {
            perror("Error binding");
            break;
        }
        size_t retCode = recv(newSoc,buffer,512,0);
        if(retCode <= 0) {
            printf("something happend or the remote closed");
            break;
        }
        httpHeader* header = parseHeader(buffer);
        if(header->type == GET) {
            handleGet(header,routes,newSoc);
        }
        close(newSoc);
    }
    close(soc);
    destroyRouteStruct(routes);
    return 0;
}

