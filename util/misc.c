#include "misc.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int execute(char *strFmt, ...)
{
	char strBuf[MAX_LINE];

	va_list ap;
	va_start(ap, strFmt);
	vsprintf(strBuf, strFmt, ap);
	va_end(ap);

	return system(strBuf);
}

char *trim(char *strBuf, char *strRst)
{
    int iLen;
    char *strFirst = strBuf;
    char *strLast;

    if (NULL == strBuf)
    {
        return NULL;
    }

    strLast = strFirst + strlen(strFirst) - 1;

    while ('\0' != *strFirst && isspace(*strFirst))
    {
        strFirst++;
    }

    while (strLast >= strFirst && isspace(*strLast))
    {
        strLast--;
    }

    iLen = strLast-strFirst+1;
    memmove(strRst, strFirst, iLen);
    strRst[iLen] = '\0';

    return strRst;
}

int get_value(char* strFileName, char* strSec, char* strKey,char* strValue)
{
    FILE *fp = NULL;

    char strBuf[MAX_LINE+1] = "\0";
    char strTmpSec[MAX_LINE] = "\0";
    char strTmpBuf[MAX_LINE] = "\0";
    char *p, *pEq;

    int iFound = -1;

    fp = fopen(strFileName, "rb");
    if (NULL == fp)
    {
        return -1;
    }

    while (0 != iFound && NULL != fgets(strBuf, MAX_LINE, fp))
    {
        p = strchr(strBuf, '\n');
        if (NULL != p)
        {
            *p = '\0';
        }

        p = strchr(strBuf, '#');
        if (NULL != p)
        {
            *p = '\0';
        }

        p = trim(strBuf, strTmpBuf);
        if ('[' == *p && ']' == *(p+strlen(p)-1))
        {
            *(p+strlen(p)-1)='\0';
            strcpy(strTmpSec, p+1);
            continue;
        }

        pEq = strchr(p, '=');
        if (NULL != pEq)
        {
            *pEq = '\0';
            trim(p, strTmpBuf);
            if (strcmp(strKey, strTmpBuf) == 0 && strcmp(strSec, strTmpSec)==0)
            {
                trim(pEq + 1, strTmpBuf);
                strcpy(strValue, strTmpBuf);
                iFound = 0;
            }
        }

    }

    fclose(fp);
    return iFound;
}

int create_threads(int n, void*(*thr_main)(void*arg))
{
	long i;
	pthread_t tid;
	for (i = 0; i < n; i++) {
		if (0 != pthread_create(&tid, NULL, thr_main, (void*)i))
		{
			return -1;
		}
	}
	return 0;
}

int sendn(int fd, const char *strBuf, int size)
{
	int iRet = 0, iCountAll = 0;

	while (iCountAll < size)
	{
		iRet = send(fd, strBuf + iCountAll, size - iCountAll, 0);
		if (iRet < 0)
		{
			return -1;
		}
		iCountAll += iRet;
	}

	return 0;
}

int sendv(int fd, char *fmt, ...)
{
	char strBuf[4096] = "\0";
	va_list ap;
	va_start(ap, fmt);
	int n = vsprintf(strBuf, fmt, ap);
	va_end(ap);
	return sendn(fd, strBuf, n);
}

int recvn(int fd, char *strBuf, int size)
{
	int iRet = 0, iRead = 0;

	while (iRead < size)
	{
		iRet = recv(fd, strBuf + iRead, size - iRead, 0);
		if (iRet <= 0)
		{
			return -1;
		}
		iRead += iRet;
	}

	return 0;
}

int tcp_listen(char *strIp, int iPort, int iListen)
{
	int iReturn = 0;
	struct sockaddr_in addrServer;
	int iOption = 1;

	int isockServer = socket(AF_INET, SOCK_STREAM, 0);
	if (isockServer < 0)
	{
		return -1;
	}
	if (setsockopt(isockServer, SOL_SOCKET, SO_REUSEADDR, &iOption,
			sizeof(iOption)) < 0)
	{
		return -1;
	}

	bzero(&addrServer, sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	inet_aton(strIp, &(addrServer.sin_addr));
	addrServer.sin_port = htons(iPort);
	iReturn = bind(isockServer, (struct sockaddr *) &addrServer,
			sizeof(addrServer));

	if (0 != iReturn)
	{
		return -1;
	}

	iReturn = listen(isockServer, iListen);

	if (0 != iReturn)
	{
		return -1;
	}

	return isockServer;
}

int tcp_connect(char *strIp, int iPort)
{
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		return -1;
	}

	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr =
	{ 0, };
	addr.sin_family = AF_INET;

	if (NULL == strIp)
	{
		addr.sin_addr.s_addr = htonl(INADDR_ANY );
	}
	else
	{
		if (1 != inet_pton(AF_INET, strIp, &addr.sin_addr))
		{
			close(fd);
			return -1;
		}
	}
	addr.sin_port = htons(iPort);

	if (connect(fd, (struct sockaddr *) &addr, addrlen) < 0)
	{
		close(fd);
		return -1;
	}
	return fd;
}


