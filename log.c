#include "log.h"
#include "util/misc.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

struct {
	char strBasePath[MAX_PATH];
} g_log_conf;

int log_init(char *strPath)
{
	strcpy(g_log_conf.strBasePath, strPath);
	if (0 != access(strPath, F_OK)) 
	{
		if (execute("mkdir -p %s", strPath) < 0)
		{
			return -1;
		}
	}
	return 0;
}

int log_(char *strFile, int iLine, int id, char *strFmt, ...)
{
	char strDate[sizeof ("20140101")] = "\0";				
	char strLogPath[MAX_PATH] = "\0";
	char strLogFileName[MAX_PATH] = "\0";

	/* 组装日志目录路径 */
	sprintf(strLogPath, "%s/%s/",
			g_log_conf.strBasePath,
			get_date(strDate));

	/* 创建目录 */
	if (0 != access(strLogPath, F_OK)) 
	{
		if (execute("mkdir -p %s", strLogPath) < 0)
		{
			return -1;
		}
	}

	sprintf(strLogFileName, "%s/%s/%d.log",
			g_log_conf.strBasePath,
			strDate,
			id);

	/* 打开日志文件 */
	FILE *logFile = fopen(strLogFileName, "ab+");
	if (NULL == logFile) 
	{
		return -1;
	}

	/* 写入日志内容 */
	fprintf(logFile, "[%-10s][%4d][", strFile, iLine);

	va_list ap;
	va_start(ap, strFmt);
	vfprintf(logFile, strFmt, ap);
	va_end(ap);

	fprintf(logFile, "]\n");

	/* 关闭日志文件 */
	fclose(logFile);
	return 0;
}


