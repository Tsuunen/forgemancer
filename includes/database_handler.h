#ifndef DATABASE_HANDLER_H
# define DATABASE_HANDLER_H

#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <uuid/uuid.h>

typedef struct s_user
{
	char	uuid[37];
	char	username[50];
	char	email[320];
	char	password_hash[72];
} User;

MYSQL	*init_conn(void);
User	get_user(char *username);
int	add_user(User user);

#endif
