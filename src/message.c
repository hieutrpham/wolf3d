
#include "cube3D.h"

int	err_message(char *string, int code)
{
	int	i;

	i = 0;
	while (string[i])
	{
		write(2, &string[i], 1);
		i++;
	}
	return (code);
}

int clean_up(char *map, char *line, int fd, int code)
{
	if(map)
		free(map);
	if(line)
		free(line);
	if(fd != -1)
		close(fd);
	return (code);
}