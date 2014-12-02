#include "conf.h"
#include "log.h"
#include "thr_main.h"
#include "util/misc.h"
#include <unistd.h>

int main()
{

	if (0 != conf_init()) {
		ERR_QUIT("初始化配置文件失败");
	}

	int MAIN_ID = get_max_thread();
	DEBUG("main id[%d]", MAIN_ID);

	if (0 != log_init(get_log_path())) {
		ERR_QUIT("初始化日志失败");
	}

	listen_fd = tcp_listen(get_ip(), get_port(), get_backlog());
	if (listen_fd < 0) {
		ERR_QUIT("监听连接失败");
	}

	if (0 != create_threads(get_max_thread(), thr_main)) {
		ERR_QUIT("创建线程失败");
	}

	LOG(MAIN_ID, "系统启动成功, 总线程数[%d]", get_max_thread());
	while(1) {
		sleep(100);
	}

	return 0;
}


