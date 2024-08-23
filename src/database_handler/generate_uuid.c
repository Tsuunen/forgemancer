#include <uuid/uuid.h>
#include "../../includes/database_handler.h"

int	verify_uuid(char *uuid)
{
	MYSQL		*conn;
	MYSQL_STMT	*stmt;
	MYSQL_BIND	bind[1], result[1];
	const char	*query = "SELECT COUNT(uuid) FROM USER WHERE uuid = ?;";
	int			count;

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
	bind[0].buffer = uuid;
	bind[0].buffer_length = sizeof(uuid);
	long unsigned length = strlen(uuid);
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

	result[0].buffer_type = MYSQL_TYPE_LONG;
	result[0].buffer = &count;
	result[0].length = 0;

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
	return (count);
}

char	*generate_uuid(void)
{
	uuid_t	raw_uuid;
	char	*uuid = malloc(37);

	uuid_generate_random(raw_uuid);
	uuid_unparse_lower(raw_uuid, uuid);
	if (verify_uuid(uuid))
		return (generate_uuid());
	return (uuid);
}
