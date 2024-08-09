#include "../../includes/database_handler.h"

int	add_user(User user)
{
	MYSQL			*conn;
	MYSQL_STMT		*stmt;
	MYSQL_BIND		bind[4];
	unsigned long	length;
	const char		*query = "INSERT INTO USER VALUES (?, ?, ?, ?);";

	conn = init_conn();
	stmt = mysql_stmt_init(conn);
	memset(bind, 0, sizeof(bind));
	if (stmt == NULL)
	{
		fprintf(stderr, "mysql_stmt_init() failed\n");
		mysql_close(conn);
		exit(EXIT_FAILURE);
	}
	if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0)
	{
		fprintf(stderr, "mysql_stmt_prepare() failed : %s\n", mysql_stmt_error(stmt));
		mysql_stmt_close(stmt);
		mysql_close(conn);
	}

	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = user.uuid;
	bind[0].buffer_length = sizeof(user.uuid);
	bind[0].length = 0;

	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer = user.username;
	bind[1].buffer_length = sizeof(user.username);
	length = strlen(user.username);
	bind[1].length = &length;

	bind[2].buffer_type = MYSQL_TYPE_STRING;
	bind[2].buffer = user.email;
	bind[2].buffer_length = sizeof(user.email);
	length = strlen(user.email);
	bind[2].length = &length;

	bind[3].buffer_type = MYSQL_TYPE_STRING;
	bind[3].buffer = user.password_hash;
	bind[3].buffer_length = sizeof(user.password_hash);
	length = strlen(user.password_hash);
	bind[3].length = &length;

	if (mysql_stmt_bind_param(stmt, bind) != 0)
	{
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
	if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

	mysql_stmt_close(stmt);
	mysql_close(conn);

	return (0);
}
