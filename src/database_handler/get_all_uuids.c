#include "../../includes/database_handler.h"

char	**get_all_uuids(void)
{
	MYSQL		*conn;
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char		**uuids_list;

	conn = init_conn();

	if (mysql_query(conn, "SELECT COUNT(uuid) FROM USER;"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	uuids_list = malloc(sizeof(*uuids_list) * (atoi(row[0]) + 1));

	if (mysql_query(conn, "SELECT uuid FROM USER;"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}


	res = mysql_store_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		*uuids_list = row[0];
		uuids_list++;
	}
	*uuids_list = NULL;

	return (uuids_list);
}
