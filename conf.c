#include "conf.h"
#include "util/misc.h"

struct {
	char ip[CONFIG_ITEM_LEN];
	char port[CONFIG_ITEM_LEN];
	char db_ip[CONFIG_ITEM_LEN];
	char db_port[CONFIG_ITEM_LEN];
	char db_user[CONFIG_ITEM_LEN];
	char db_pass[CONFIG_ITEM_LEN];
	char log_path[CONFIG_ITEM_LEN];
	char max_thread[CONFIG_ITEM_LEN];
	char backlog[CONFIG_ITEM_LEN];
} g_config;

int conf_init()
{
#define LOAD_VAL(SEC, KEY, VAL) \
	do { \
		int iRet = get_value(CONF_FILE, SEC, KEY, VAL); \
		if (iRet < 0) \
		{ \
			return -1; \
		} \
	} while (0);
	LOAD_VAL("cloud", "ip", g_config.ip);
	LOAD_VAL("cloud", "port", g_config.port);
	LOAD_VAL("cloud", "db_ip", g_config.db_ip);
	LOAD_VAL("cloud", "db_port", g_config.db_port);
	LOAD_VAL("cloud", "db_user", g_config.db_user);
	LOAD_VAL("cloud", "db_pass", g_config.db_pass);
	LOAD_VAL("cloud", "log_path", g_config.log_path);
	LOAD_VAL("cloud", "max_thread", g_config.max_thread);
	LOAD_VAL("cloud", "backlog", g_config.backlog);
#undef LOAD_VAL
	return 0;
}

char *get_ip()
{
	return g_config.ip;
}
int get_port()
{
	return atoi(g_config.port);
}
char *get_db_ip()
{
	return g_config.db_ip;
}
int get_db_port()
{
	return atoi(g_config.db_port);
}
char *get_db_user()
{
	return g_config.db_user;
}
char *get_db_pass()
{
	return g_config.db_pass;
}
char *get_log_path()
{
	return g_config.log_path;
}

int get_max_thread()
{
	return atoi(g_config.max_thread);
}
int get_backlog()
{
	return atoi(g_config.backlog);
}
