/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:28:46 by trupham           #+#    #+#             */
/*   Updated: 2025/12/13 12:12:10 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

#define ft_strdup strdup
#define ft_realloc realloc
#define ft_calloc calloc

t_str *str_append(t_str *str, char *line)
{
	int i;

	i = 0;
	if (str->count >= str->cap)
	{
		if (str->cap == 0)
			str->cap = 256;
		else
			str->cap *=2;
		str->str = ft_realloc(str->str, str->cap * sizeof(*str->str));
	}
	while (line[i] != '\n')
		str->str[str->count++] = line[i++];
	return str;
}
// only check have the character or not, not enough to check
//- any conflicts
//- any error after direction, floor and ceil color is correct or not
//- position of direction couldn't be after F,C
void parse(t_file *files, char *line)
{
	if (ft_strncmp(line, "NO", 2))
		files->no = ft_strdup(line);
	else if (ft_strncmp(line, "SO", 2))
		files->so = ft_strdup(line);
	else if (ft_strncmp(line, "WE", 2))
		files->we = ft_strdup(line);
	else if (ft_strncmp(line, "EA", 2))
		files->ea = ft_strdup(line);
	else if (ft_strncmp(line, "F", 1))
		files->floor = ft_strdup(line);
	else if (ft_strncmp(line, "C", 1))
		files->ceil = ft_strdup(line);
	else
		str_append(files->map, line);
}

int main(int argc, char *argv[])
{
	t_game 	*game;
	
	if (argc != 2)
		return (err_message("Usage: ./cub3D <map.cub>\n", FAIL));
	//check extension file
	if (check_file(argv[1]) == FAIL)
		return (err_message("map is wrong\n", FAIL));
	//open file
	printf("Start to load map\n");
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("%m\n"));
	//init game
	static t_file files = {0};
	files.map = calloc(1, sizeof(*files.map));
	// read map
	while(true)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		parse(&files, line);
		free(line);
	}
	close(fd);
	printf("%s\n", files.map->str);
	//check map
	//need to check it must be border by wall-1, don't have any empty-0
	//don't have 2 players-P,
	//about exit - E, maybe allowed 1 exit

	//init game
	game = calloc(1, sizeof(t_game));
	//start to display
	start_to_display(game, &files);
	//free game
	return (SUCC);
}

int check_file(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '.' && str[i])
		i++;
	if (ft_strcmp(&str[i + 1], "cub") == 0 && (str[i + 4] == '\0'))
		return (SUCC);
	return (FAIL);
}
