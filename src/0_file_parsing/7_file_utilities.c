/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_file_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:04:41 by trupham           #+#    #+#             */
/*   Updated: 2026/02/16 11:04:42 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

char	*get_path(char *line)
{
	char	*out;
	int		len;
	int		i;

	len = ft_strlen(line);
	out = malloc(len);
	if (!out)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
	{
		out[i] = line[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

void	skip_space(char **str)
{
	while (**str == ' ')
		(*str)++;
}

int	find_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '0')
			return (FAIL);
		i++;
	}
	return (SUCC);
}

void	print_file(t_file *file)
{
	printf("Value of path: %s\n %s\n %s\n %s\n", file->no_path, file->so_path,
		file->we_path, file->ea_path);
	printf("Value of direction: %d %d %d %d %d %d\n", file->no, file->so,
		file->we, file->ea, file->fl, file->ce);
	printf("Value of floor color: %d %d %d\n", file->fl_rgb[0], file->fl_rgb[1],
		file->fl_rgb[2]);
	printf("Value of ceiling color: %d %d %d\n", file->ce_rgb[0],
		file->ce_rgb[1], file->ce_rgb[2]);
}
