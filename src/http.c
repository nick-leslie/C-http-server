//
// Created by nickl on 10/31/23.
//

#include "http.h"
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <malloc.h>
#include <linux/limits.h>

httpHeader* parseHeader(char* reuqest) {
    httpHeader* header = malloc(sizeof(httpHeader) + 1);
    char* token = NULL;
    char space[2] = " ";
    token = strtok(reuqest,space);
    if(strcmp(token,"GET") == 0) {
        header->type = GET;
    } else if(strcmp(token,"POST") == 0) {
        header->type = POST;
    } else {
        header->type = UNHANDLED;
    }
    token = strtok(NULL,space);
    header->route = malloc(strlen(token) * sizeof(char));
    strncpy(header->route,token,strlen(token) * sizeof(char));
    header->route[strlen(token) * sizeof(char)] = '\0';
    return header;
}

void handleGet(httpHeader* header,getRoutes* routes,int soc) {
    char* fileBuffer;
    long fileSize = 0;
    char fullPath[PATH_MAX];
    if(strcmp(header->route,"/") == 0) {
        sprintf(fullPath,"%s/%s",routes->baseDirPath,"index.html");
        fileSize = readFileToBuffer(fullPath,&fileBuffer);
    } else {
        struct stringLinkedList* current = routes->routes;
        while (current != NULL)  {
            if(strcmp(header->route,current->data)==0) {
                sprintf(fullPath,"%s/%s",routes->baseDirPath,current->data);
                fileSize = readFileToBuffer(fullPath,&fileBuffer);
            }
            current = current->next;
        }
    }
    if(fileSize != 0) {
        dprintf(soc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n", fileSize);
        send(soc, fileBuffer, fileSize, 0);
    } else {
        const char *c404 = "HTTP/1.1 404 Not Found\r\n"   "Connection: close\r\n"  "Content-Length: 9\r\n\r\nNot Found";
        send(soc, c404, strlen(c404),0);
    }
}