
#include "../include/cube3D.h"

int	parse_floor(t_file *file, char *line)
{
	file->fl++;
	if (file->fl > 1)
		return (err_message("duplicate floor\n", FAIL));
	return (check_fc(file, line, "F "));
}

int	parse_ceil(t_file *file, char *line)
{
	file->ce++;
	if (file->ce > 1)
		return (err_message("duplicate ceil\n", FAIL));
	return (check_fc(file, line, "C "));
}

int	check_fc(t_file *file, char *line, char *dir)
{
	int	i;
	
	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(dir, &line[i], 2) == 0)
		return (FAIL);
	else
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(dir, "F ", 2))
		return (check_color(&line[i], file->fl_rgb));
	else if (ft_strncmp(dir, "C ", 2))
		return (check_color(&line[i], file->ce_rgb));
	return (FAIL);
}

int	check_color(char *num, int *color)
{
	int	i;

	i = 0;
	color[0] = check_value(num, &i);
	if (color[0] == FAIL || num[i++] != ',')
		return (FAIL);
	color[1] = check_value(num, &i);
	if (color[1] == FAIL || num[i++] != ',')
		return (FAIL);
	color[2] = check_value(num, &i);
	if (color[2] == FAIL)
		return (FAIL);
	return (SUCC);
}

int	check_value(char *num, int *i)
{
	int	out;

	out = 0;
	if (!(num[*i] >= '0' && num[*i] <= '9'))
		return (err_message("color has invalid character\n", FAIL));
	while (num[*i] >= '0' && num[*i] <= '9')
	{
		out = out * 10 + (num[*i] - '0');
		if (out > 255)
			return (err_message("color has number over 255\n", FAIL));
		(*i)++;
	}
	return (out);
}
