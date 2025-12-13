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

void parse(t_game *games, char *line)
{
	if (ft_strncmp(line, "NO", 2))
		games->no = ft_strdup(line);
	else if (ft_strncmp(line, "SO", 2))
		games->so = ft_strdup(line);
	else if (ft_strncmp(line, "WE", 2))
		games->we = ft_strdup(line);
	else if (ft_strncmp(line, "EA", 2))
		games->ea = ft_strdup(line);
	else if (ft_strncmp(line, "F", 1))
		games->floor = ft_strdup(line);
	else if (ft_strncmp(line, "C", 1))
		games->ceil = ft_strdup(line);
	else
		str_append(games->map, line);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (err_message("Usage: ./cub3D <map.cub>\n", FAIL));
	if (check_file(argv[1]) == FAIL)
		return (err_message("map is wrong\n", FAIL));
	printf("Start to load map\n");
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("%m\n"));
	static t_game games = {0};
	games.map = calloc(1, sizeof(*games.map));

	while(true)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		parse(&games, line);
		free(line);
	}
	printf("%s\n", games.map->str);
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
