#include "misc.h"
#include <time.h>

char *get_date(char *strBuf)
{
	time_t now = time(NULL);
	struct tm tm_now;

	localtime_r(&now, &tm_now);
	strftime(strBuf, sizeof ("20140101"), "%Y%m%d", &tm_now);

	return strBuf;
}
