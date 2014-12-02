#ifndef MISC_H
#define MISC_H

#include <stdlib.h>
#include <stdio.h>

#define LINE() (printf("[%10s][%-4d]:", __FILE__, __LINE__)) 
#define ERR_QUIT(msg) (LINE(), puts(msg), exit(-1))
#define DEBUG(...) (LINE(), printf(__VA_ARGS__), puts(""))

#define MAX_PATH 128
#define MAX_LINE 4096

int execute(char *strFmt, ...);
int get_value(char* strFileName, char* strSec, char* strKey,char* strValue);
char *get_date(char *strBuf);
int create_threads(int n, void*(*thr_main)(void *arg));

int tcp_connect(char *strIp, int iPort);
int tcp_listen(char *strIp, int iPort, int iListen);
int recvn(int fd, char *strBuf, int size);
int sendv(int fd, char *fmt, ...);
int sendn(int fd, const char *strBuf, int size);

#endif

