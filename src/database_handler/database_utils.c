#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MYSQL	*init_conn(void)
{
	MYSQL			*conn;
	const char		*server = getenv("DB_SERVER");
	const char		*user = getenv("DB_USER");
	const char		*password = getenv("DB_PASSWORD");
	const char		*database = getenv("DB_DATABASE");
	unsigned int	port = atoi(getenv("DB_PORT"));

	if (port == 0)
	{
		fprintf(stderr, "Port must be an int\n");
		exit(1);
	}

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server, user, password, database, port, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	return (conn);
}
