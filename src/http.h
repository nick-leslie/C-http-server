
//
// Created by nickl on 10/31/23.
//


#include "files.h"

#ifndef SERVER_HTTP_H
#define SERVER_HTTP_H

#endif //SERVER_HTTP_H
enum requestType {
    GET,
    POST,
    UNHANDLED
};

typedef struct {
    enum requestType type;
    char* route;
} httpHeader;

httpHeader* parseHeader(char* httpRequest);

void handleGet(httpHeader* header,getRoutes* routes,int soc);
