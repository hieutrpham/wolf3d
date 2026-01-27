
#include "../include/cube3D.h"

void	find_height_width(t_file *file, char **map)
{
	int	height;
	int	width;
	int	len;

	height = 0;
	width = 0;
	while (map[height])
	{
		len = ft_strlen(map[height]);
		if (len > width)
			width = len;
		height++;
	}
	file->map_height = height;
	file->map_width = width;
}

void	find_player_pos(t_file *file)
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

// int	flood_fill(char **map, int x, int y, int w, int h)
// {
// 	if (x < 0 || y < 0 || x >= w || y >= h)
// 		return (FAIL);
// 	if (map[y][x] == ' ')
// 		return (FAIL);
// 	if (map[y][x] == '1' || map[y][x] == 'V')
// 		return (SUCC);
// 	map[y][x] = 'V';
// 	if (flood_fill(map, x + 1, y, w, h) == FAIL)
// 		return (FAIL);
// 	if (flood_fill(map, x -1, y, w, h) == FAIL)
// 		return (FAIL);
// 	if (flood_fill(map, x, y + 1, w, h) == FAIL)
// 		return (FAIL);
// 	if (flood_fill(map, x, y - 1, w, h) == FAIL)
// 		return (FAIL);
// 	return (SUCC);
// }

int	flood_fill(char **map, int x, int y, t_bounds b)
{
	if (x < 0 || y < 0 || x >= b.w || y >= b.h)
		return (FAIL);
	if (map[y][x] == ' ')
		return (FAIL);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (SUCC);
	map[y][x] = 'V';
	if (flood_fill(map, x + 1, y, b) == FAIL)
		return (FAIL);
	if (flood_fill(map, x -1, y, b) == FAIL)
		return (FAIL);
	if (flood_fill(map, x, y + 1, b) == FAIL)
		return (FAIL);
	if (flood_fill(map, x, y - 1, b) == FAIL)
		return (FAIL);
	return (SUCC);
}

int	is_walkable(char c)
{
	return (c == '0');
}

int	player_can_move(t_file *file)
{
	int	x;
	int	y;

	x = file->player_x;
	y = file->player_y;
	if (is_walkable(file->parse_map[y][x + 1]))
		return (SUCC);
	if (is_walkable(file->parse_map[y][x - 1]))
		return (SUCC);
	if (is_walkable(file->parse_map[y + 1][x]))
		return (SUCC);
	if (is_walkable(file->parse_map[y - 1][x]))
		return (SUCC);
	return (FAIL);
}
