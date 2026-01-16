
#include "../include/cube3D.h"

void free_file(t_file *file)
{
	if (file->no_path)
		free(file->no_path);
	if (file->so_path)
		free(file->so_path);
	if (file->we_path)
		free(file->we_path);
	if (file->ea_path)
		free(file->ea_path);
    file->no_path = NULL;
    file->so_path = NULL;
    file->we_path = NULL;
    file->ea_path = NULL;
	if (file->map)
		free(file->map);
	if (file ->parse_map)
		free_2d_array(file->parse_map);
	if (file->fd != -1)
		close(file->fd);
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

void free_2d_array(char **str)
{
	int	i;

	if(!str)
		return;
	i = 0;
	while (str[i])
	{
		if(str[i])
			free(str[i]);
		i++;
	}
	free(str);
}