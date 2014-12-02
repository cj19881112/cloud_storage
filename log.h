#ifndef LOG_H
#define LOG_H

#define LOG(id, ...) log_(__FILE__, __LINE__, id, __VA_ARGS__)

int log_init(char *strPath);
int log_(char *file, int line, int id, char *fmt, ...);

#endif

