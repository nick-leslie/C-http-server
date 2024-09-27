//
// Created by nickl on 10/31/23.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "files.h"

long readFileToBuffer(char* path, char** buffer) {
    FILE* file = fopen(path,"r");
    if(file == NULL) {
        return 0;
    }
    //get file size
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    *buffer = malloc(sizeof(char) * fsize +1);
    memset(*buffer,0,fsize+1);
    fread(*buffer,sizeof(char),fsize,file);
    fclose(file);
    return fsize;
}
int recerseDirectoryConstructRoute(char* baseDirPath,char* subRoutes,getRoutes* routes) {
    char fullPath[PATH_MAX];
    char urlPath[PATH_MAX];
    DIR* FD = opendir(baseDirPath);
    struct dirent* file_info;
    if(FD == NULL) {
        perror("Error opening dir:");
        return -1;
    }
    while ((file_info = readdir(FD)) != 0) {
        struct stat path_stat;
        stat(file_info->d_name, &path_stat);
        sprintf(fullPath, "%s/%s", baseDirPath, file_info->d_name);
        sprintf(urlPath, "%s/%s", subRoutes, file_info->d_name);
        stat(fullPath, &path_stat);
        if(S_ISDIR(path_stat.st_mode)) {
            if(strcmp(file_info->d_name,".\0") != 0 && strcmp(file_info->d_name,"..\0") != 0) {
                recerseDirectoryConstructRoute(fullPath, urlPath, routes);
            }
        } else {
            pushString(&routes->routes,urlPath);
        }
    }
    closedir(FD);
    return 0;
}


getRoutes* constructRoutesStruct(char* baseDirPath) {
    char path[PATH_MAX];
    getRoutes* routes = malloc(sizeof(getRoutes) + 1);
    routes->routes = NULL;
    //routes->baseDirPath = malloc(strlen(baseDirPath) * sizeof(char));
    strncpy(routes->baseDirPath,baseDirPath,strlen(baseDirPath) * sizeof(char));
    routes->baseDirPath[strlen(baseDirPath) * sizeof(char)] = '\0';
    DIR* FD = opendir(baseDirPath);
    struct dirent* file_info;
    if(FD == NULL) {
        free(routes);
        perror("Error opening dir:");
        return NULL;
    }
    while ((file_info = readdir(FD)) != 0) {
        struct stat path_stat;
        sprintf(path,"%s/%s",baseDirPath,file_info->d_name);
        stat(path, &path_stat);
        if(S_ISDIR(path_stat.st_mode) != 0) {
            if(strcmp(file_info->d_name,".\0") != 0 && strcmp(file_info->d_name,"..\0") != 0) {
                char* name = malloc((strlen(file_info->d_name)+1)*sizeof(char));
                sprintf(name,"/%s",file_info->d_name);
                recerseDirectoryConstructRoute(path,name, routes);
            }
        } else {
            char* name = malloc((strlen(file_info->d_name)+1)*sizeof(char));
            sprintf(name,"/%s",file_info->d_name);
            pushString(&routes->routes,name);
        }
    }
    closedir(FD);
    return routes;
}

void destroyRouteStruct(getRoutes* routes) {
    freeLinkedList(routes->routes);
    free(routes);
}
