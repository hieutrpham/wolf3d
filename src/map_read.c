
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
	return (SUCC);
}

int map_check(t_file *file)
{
	char **map_2d_draft;

	if(!file || !file->map)
		return (FAIL);
	if (map_wrong_character(file) == FAIL)
		return (FAIL);
	if (map_empty(file) == FAIL)
		return (err_message("Empty line inside map\n", FAIL));
	// printf("Value of map: %s\n", file->map);
	map_2d_draft = ft_split(file->map, '\n');
	if(!map_2d_draft)
		return (err_message("Copy map error\n", FAIL));
	find_height_width(file, map_2d_draft);
	// printf("Height of map: %d\n", file->map_height);
	// printf("Width of map: %d\n", file->map_width);
	file->parse_map = pad_map(file, map_2d_draft);
	free_2d_array(map_2d_draft);
	if(!file->parse_map)
		return (FAIL);
	// print_map(file->parse_map);
	find_player_pos(file);
	if (player_can_move(file) == FAIL)
		return (err_message("Player cannot move\n", FAIL));
	if (check_map_close(file) == FAIL)
		return (FAIL);
	return(SUCC);
}

int map_wrong_character(t_file *file)
{
	int		i;
	char	c;
	int		no_player;

	i = 0;
	no_player = 0;
	while(file->map[i])
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

char **pad_map(t_file *file, char **map)
{
	char	**map_after;
	int		i;
	int		j;

	map_after = malloc(sizeof(char *) * (file->map_height + 1));
	if (!map_after)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map_after[i] = malloc(file->map_width + 1);
		if (!map_after[i])
		{
			clear_previous(map_after, i);
			return (NULL);
		}
		j = 0;
		while(map[i][j])
		{
			map_after[i][j] = map[i][j];
			j++;
		}
		while(j < file->map_width)
		{
			map_after[i][j] = ' ';
			j++;
		}
		map_after[i][j] = '\0';
		i++;
	}
	map_after[file->map_height] = NULL;
	return (map_after);
}

int check_map_close(t_file *file)
{
	char	**map_flood;
	int		res;

	if (!file->parse_map)
		return (FAIL);
	map_flood = arr_2d_copy(file->parse_map, file->map_height);
	if (!map_flood)
		return (err_message("Copy map for flood fail\n", FAIL));
	res = flood_fill(map_flood, file->player_x, file->player_y, file->map_width, file->map_height);
	free_2d_array(map_flood);
	if (res == FAIL)
		return (err_message("Map is not closed\n", FAIL));
	return (SUCC);
}

int is_walkable(char c)
{
	return (c == '0');
}

int player_can_move(t_file *file)
{
	int x = file->player_x;
	int y = file->player_y;

	/* Right */
	if (is_walkable(file->parse_map[y][x + 1]))
		return (SUCC);
	/* Left */
	if (is_walkable(file->parse_map[y][x - 1]))
		return (SUCC);
	/* Down */
	if (is_walkable(file->parse_map[y + 1][x]))
		return (SUCC);
	/* Up */
	if (is_walkable(file->parse_map[y - 1][x]))
		return (SUCC);

	return (FAIL);
}

