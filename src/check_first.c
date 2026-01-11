
#include "../include/cube3D.h"

int check_first(char *line, int *res)
{
	int		j;

	j = 0;
	while(j < 6)
	{
		if (res[j] > 1)
			return(err_message("duplicate direction\n", FAIL));
		j++;
	}
	if (check_dir("NO", line) == SUCC)
		res[0]++;
	else if (check_dir("SO", line) == SUCC)
		res[1]++;
	else if (check_dir("WE", line) == SUCC)
		res[2]++;
	else if (check_dir("EA", line) == SUCC)
		res[3]++;
	else if (check_fc('F', line) == SUCC)
		res[4]++;
	else if (check_fc('C', line) == SUCC)
		res[5]++;
	else
		return (FAIL);
	return (SUCC);
}

int check_dir(char *dir, char *line)
{
	int	i;
	int	fd;

	if (!dir || !line)
		return (FAIL);
	i = 0 ;
	while(line[i] == ' ')
		i++;
	if (line[i] == dir[0] && line[i + 1] == dir[1])
		i = i + 2;
	else
		return (FAIL);
	while(line[i] == ' ')
		i++;
	fd = open(&line[i], O_RDONLY);
	if (fd == -1)
		return(err_message("path of direction error\n", FAIL));
	close (fd);
	return (SUCC);
}

int check_fc(char c, char *line)
{
	int	i;

	if (!c || !line)
		return (FAIL);
	i = 0;
	while(line[i] == ' ')
		i++;
	if (line[i] == c)
		i++;
	else
		return (FAIL);
	while(line[i] == ' ')
		i++;
	return(check_color(&line[i]));
}

int check_color(char *num)
{
	int r_val;
	int g_val;
	int b_val;
	int	i;
	
	i = 0;
	r_val = check_value(num, &i);
	if (r_val == FAIL || num[i++] != ',')
		return (FAIL);
	g_val = check_value(num, &i);
	if (g_val == FAIL || num[i++] != ',')
		return (FAIL);
	b_val = check_value(num, &i);
	if (b_val == FAIL || num[i++] != ',')
		return (FAIL);
	return (SUCC);
}

int check_value(char *num, int *i)
{
	int out;

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
	return(out);
}
