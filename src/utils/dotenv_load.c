#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	load_env_variables(const char *file_path)
{
	FILE	*file;
	char	line[256];
	char	*delimiter;
	char	*key;
	char	*value;

	file = fopen(file_path, "r");
	if (file == NULL)
	{
		perror("Failed to open .env file");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == '\n' || line[0] == '#')
			continue;

		line[strcspn(line, "\n")] = '\0';
		delimiter = strchr(line, '=');
		if (delimiter == NULL)
			continue;

		*delimiter = '\0';
		key = line;
		value = delimiter + 1;
		setenv(key, value, 1);
	}
	fclose(file);
}
