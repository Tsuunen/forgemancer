#include "../../includes/database_handler.h"

User	get_user(char *username)
{
	MYSQL		*conn;
	MYSQL_STMT	*stmt;
	MYSQL_BIND	bind[1], result[3];
	const char	*query = "SELECT uuid, email, password_hash FROM USER WHERE username = ?";
	User		user;

	memset(&user, 0, sizeof(User));
	strncpy(user.username, username, sizeof(user.username) - 1);
	conn = init_conn();
	stmt = mysql_stmt_init(conn);
	memset(bind, 0, sizeof(bind));
	memset(result, 0, sizeof(result));
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
	bind[0].buffer = username;
	bind[0].buffer_length = sizeof(username);
	long unsigned length = strlen(username);
	bind[0].length = &length;
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

	result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = user.uuid;
    result[0].buffer_length = sizeof(user.uuid);

	result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = user.email;
    result[1].buffer_length = sizeof(user.email);

	result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = user.password_hash;
    result[2].buffer_length = sizeof(user.password_hash);
	if (mysql_stmt_bind_result(stmt, result) != 0)
	{
		fprintf(stderr, "mysql_stmt_bind_result() failed: %s\n", mysql_stmt_error(stmt));
		mysql_stmt_close(stmt);
		mysql_close(conn);
		exit(EXIT_FAILURE);
    }

	int fetch_status = mysql_stmt_fetch(stmt);
	if (fetch_status == 1 || fetch_status == MYSQL_NO_DATA) {
		fprintf(stderr, "No data or error occurred: %s\n", mysql_stmt_error(stmt));
		mysql_stmt_close(stmt);
		mysql_close(conn);
		exit(EXIT_FAILURE);
	}

	mysql_stmt_close(stmt);
	mysql_close(conn);
	return (user);
}
