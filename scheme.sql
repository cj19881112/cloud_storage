create database cloud;
use cloud;
	
create table t_user (
		id 		int(10) primary key auto_increment, /* 用户id */
		name 	char(32),	/* 用户名 */
		pass 	char(32)	/* 密码 */
);

create table t_file (
		id 		int(10) primary key auto_increment, /* 文件id */
		pid 	int(10),		/* 父节点id */
		uid 	int(10),		/* 用户id */
		path 	varchar(256),	/* 绝对路径 */
		is_dir 	char(1),		/* 是否目录 */
		md5 	char(32),		/* 文件md5码 */
		size 	char(10),		/* 文件大小 */
		ctime 	char(20)		/* 创建时间 */
);

