
#include "../include/cube3D.h"

static int	pad_row(char *dest, char *src, int width);

int	map_read_from_file(t_file *file, char *line)
{
	char	*new_map;

	if (!line)
		return (SUCC);
	if (file->line_count == 0 && file->map == NULL)
	{
		file->map = ft_strdup(line);
		if (!file->map)
			return (err_message("Join map error\n", FAIL));
	}
	else
	{
		new_map = ft_strjoin(file->map, line);
		if (!new_map)
			return (err_message("Join map error\n", FAIL));
		free(file->map);
		file->map = new_map;
	}
	file->line_count++;
	return (SUCC);
}

char	**pad_map(t_file *file, char **map)
{
	char	**map_after;
	int		i;

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
		pad_row(map_after[i], map[i], file->map_width);
		i++;
	}
	map_after[file->map_height] = NULL;
	return (map_after);
}

static	int	pad_row(char *dest, char *src, int width)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	while (j < width)
	{
		dest[j] = ' ';
		j++;
	}
	dest[j] = '\0';
	return (0);
}

char	**arr_2d_copy(char **str, int len)
{
	char	**str_copy;
	int		i;

	if (!str)
		return (NULL);
	str_copy = malloc(sizeof(char *) * (len + 1));
	if (!str_copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str_copy[i] = ft_strdup(str[i]);
		if (!str_copy[i])
		{
			clear_previous(str_copy, i);
			return (NULL);
		}
		i++;
	}
	str_copy[len] = NULL;
	return (str_copy);
}
