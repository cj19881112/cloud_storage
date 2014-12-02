#ifndef CONF_H
#define CONF_H

#define CONF_FILE "cloud.ini"
#define CONFIG_ITEM_LEN 128

int conf_init();
char *get_ip();
int get_port();
char *get_db_ip();
int get_db_port();
char *get_db_user();
char *get_db_pass();
char *get_log_path();
int get_max_thread();
int get_backlog();

#endif
