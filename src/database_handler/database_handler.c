#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int	get_user(char *uuid)
{
	MYSQL			*conn;
	MYSQL_RES		*res;
	MYSQL_ROW		row;

	const char		*server = getenv("DB_SERVER");
	const char		*user = getenv("DB_USER");
	const char		*password = getenv("DB_PASSWORD");
	const char		*database = getenv("DB_DATABASE");
	unsigned int	port = atoi(getenv("DB_PORT"));
	if (port == 0)
	{
		perror("Port must be an int");
		exit(1);
	}

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server, user, password, database, port, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	if (mysql_query(conn, "SELECT * FROM USER;"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s, %s, %s, %s", row[0], row[1], row[2], row[3]);

	mysql_free_result(res);
	mysql_close(conn);

	return (0);
}
