
#include "../include/cube3D.h"

void print_map(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(map[i])
	{
		printf("row %d is :\n", i);
		j = 0;
		while(map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void find_height_width(t_file *file, char **map)
{
	int height;
	int width;
	int len;

	height = 0;
	width = 0;
	while(map[height])
	{
		len = ft_strlen(map[height]);
		if (len > width)
			width = len;
		height++;
	}
	file->map_height = height;
	file->map_width = width;
}

void clear_previous(char **str, int len)
{
	int i;

	if(!str || !str[0])
		return;
	i = 0;
	while (i < len)
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void find_player_pos(t_file *file)
{
	int	i;
	int	j;

	if (!file->parse_map)
		return ;
	i = 0;
	while (i < file->map_height)
	{
		j = 0;
		while (j < file->map_width)
		{
			if (file->parse_map[i][j] == 'N' || file->parse_map[i][j] == 'S'
				||file->parse_map[i][j] == 'W' || file->parse_map[i][j] == 'E')
			{
				file->player_y = i;
				file->player_x = j;
				file->player_dir = file->parse_map[i][j];
			}
			j++;
		}
		i++;
	}
}

char **arr_2d_copy(char **str, int len)
{
	char	**str_copy;
	int 	i;

	if (!str)
		return (NULL);
	str_copy = malloc(sizeof(char *) * (len + 1));
	if (!str_copy)
		return (NULL);
	i = 0;
	while(i < len)
	{
		str_copy[i] = ft_strdup(str[i]);
		if(!str_copy[i])
		{
			clear_previous(str_copy, i);
			return (NULL);
		}
		i++;
	}
	str_copy[len] = NULL;
	return(str_copy);
}

int flood_fill(char **map, int x, int y, int w, int h)
{
	if (x < 0 || y < 0 || x >= w || y >= h)
		return (FAIL);
	if (map[y][x] == ' ')
		return (FAIL);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (SUCC);
	map[y][x] = 'V';
	if (flood_fill(map, x + 1, y, w, h) == FAIL)
		return (FAIL);
	if (flood_fill(map, x -1, y, w, h) == FAIL)
		return (FAIL);
	if (flood_fill(map, x, y + 1, w, h) == FAIL)
		return (FAIL);
	if (flood_fill(map, x, y - 1, w, h) == FAIL)
		return (FAIL);
	return (SUCC);
}