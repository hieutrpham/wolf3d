
#include "../include/cube3D.h"

int	map_check(t_file *file)
{
	char	**map_2d_draft;

	if (!file || !file->map)
		return (FAIL);
	if (map_wrong_character(file) == FAIL)
		return (FAIL);
	if (map_empty(file) == FAIL)
		return (err_message("Empty line inside map\n", FAIL));
	// printf("Value of map: %s\n", file->map);
	map_2d_draft = ft_split(file->map, '\n');
	if (!map_2d_draft)
		return (err_message("Copy map error\n", FAIL));
	find_height_width(file, map_2d_draft);
	// printf("Height of map: %d\n", file->map_height);
	// printf("Width of map: %d\n", file->map_width);
	file->parse_map = pad_map(file, map_2d_draft);
	free_2d_array(map_2d_draft);
	if (!file->parse_map)
		return (FAIL);
	print_map(file->parse_map);
	find_player_pos(file);
	if (player_can_move(file) == FAIL)
		return (err_message("Player cannot move\n", FAIL));
	if (check_map_close(file) == FAIL)
		return (FAIL);
	return (SUCC);
}

int	map_wrong_character(t_file *file)
{
	int		i;
	char	c;
	int		no_player;

	i = 0;
	no_player = 0;
	while (file->map[i])
	{
		c = file->map[i];
		if (c != ' ' && c != '0' && c != '1' && c != '\n'
			&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
			return (err_message("Wrong character in map\n", FAIL));
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			no_player++;
		i++;
	}
	if (no_player > 1 || no_player == 0)
		return (err_message("No of player is wrong\n", FAIL));
	return (SUCC);
}

int	map_empty(t_file *file)
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

int	check_map_close(t_file *file)
{
	char		**map_flood;
	int			res;
	t_bounds	b;

	if (!file->parse_map)
		return (FAIL);
	map_flood = arr_2d_copy(file->parse_map, file->map_height);
	if (!map_flood)
		return (err_message("Copy map for flood fail\n", FAIL));
	b.w = file->map_width;
	b.h = file->map_height;
	// res = flood_fill(map_flood, file->player_x,
	// 		file->player_y, file->map_width, file->map_height);
	res = flood_fill(map_flood, file->player_x, file->player_y, b);
	free_2d_array(map_flood);
	if (res == FAIL)
		return (err_message("Map is not closed\n", FAIL));
	return (SUCC);
}
