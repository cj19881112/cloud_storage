#include "thr_main.h"
#include "log.h"
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int listen_fd;
pthread_mutex_t leader_lock = PTHREAD_MUTEX_INITIALIZER;

int cloud_server(int id, int cli_fd);

void *thr_main(void *v)
{
	int cli_fd = 0; 
	long id = (long)v;

	LOG(id, "线程启动成功，开始接受连接");
	while (1)
	{
		pthread_mutex_lock(&leader_lock);
		do {
			cli_fd = accept(listen_fd, NULL, NULL);
		} while (cli_fd < 0 && EINTR == errno);
		pthread_mutex_unlock(&leader_lock);

		if (cli_fd < 0) {
			LOG(id, "调用accept失败,错误码[%s]，线程退出", strerror(errno));
			return ((void*)-1);
		}

		LOG(id, "接收到一个请求");
		int err = cloud_server(id, cli_fd);
		LOG(id, "请求处理完毕，结果[%d]", err);
	}

	return ((void*)0);
}

int cloud_server(int id, int cli_fd)
{
	return 0;
}






