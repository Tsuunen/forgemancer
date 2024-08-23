#include "../includes/utils.h"
#include "../includes/database_handler.h"

int	main(int ac, char **av)
{
	load_env_variables(".env");
	char	*uuid = generate_uuid();
	printf("%s\n", uuid);
	return (0);
}
