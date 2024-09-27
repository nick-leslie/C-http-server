//
// Created by nickl on 10/31/23.
//
#include "linkedList.h"
#include <limits.h>
#ifndef SERVER_FILES_H
#define SERVER_FILES_H

#endif //SERVER_FILES_H



typedef struct  {
    long numRoutes;
    char baseDirPath[PATH_MAX];
    struct stringLinkedList* routes;
}getRoutes;

long readFileToBuffer(char* path,char** buffer);

getRoutes* constructRoutesStruct(char* baseDirPath);

void destroyRouteStruct(getRoutes* routes);