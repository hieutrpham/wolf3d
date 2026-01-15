
#include "../include/cube3D.h"

int map_read(t_file *file, char *line)
{
	char	*new_map;

	if (!line)
		return (SUCC);
	if (file->line_count == 0 && file->map == NULL)
	{
		file->map = ft_strdup(line);
		if(!file->map)
			return (err_message("Join map error\n", FAIL));
	}
	else
	{
		new_map= ft_strjoin(file->map, line);
		if (!new_map)
			return (err_message("Join map error\n", FAIL));
		free(file->map);
		file->map = new_map;
	}
	file->line_count++;
	printf("Value of line count: %d\n", file->line_count);
	printf("Value of map: %s", file->map);
	return (SUCC);
}

int map_check(t_file *file)
{

	if(!file || !file->map)
		return (FAIL);
	if (map_wrong_character(file) == FAIL)
		return (err_message("Wrong character in map\n", FAIL));
	if (map_empty(file) == FAIL)
		return (err_message("Empty line inside map\n", FAIL));
	printf("Map is ok\n");
	return(SUCC);
}

int map_wrong_character(t_file *file)
{
	int		i;
	char	c;

	i = 0;
	while(file->map[i])
	{
		c = file->map[i];
		if (c != ' ' && c != '0' && c != '1' && c != '\n'
			&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
			return (FAIL);
		i++;
	}
	return(SUCC);
}

int map_empty(t_file *file)
{
	int	i;

	i = 0;
	while (file->map[i] && file->map[i + 1])
	{
		
		if (file->map[i] == '\n' && file->map[i + 1] == '\n')
			return (FAIL);
		i++;
	}
	return (SUCC);
}