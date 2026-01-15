
#include "../include/cube3D.h"

int check_exter(char *str)
{
	int	i;
	int len;

	i = 0;
	if (!str)
		return (FAIL);
	len = ft_strlen(str);
	if (len < 5)
		return (FAIL);
	while (str[i] != '.' && str[i])
		i++;
	if (i == len)
		return(FAIL);
	if (ft_strcmp(&str[i + 1], "cub") == 0 && (str[i + 4] == '\0'))
		return (SUCC);
	return (FAIL);
}

int	check_inter(t_file *file, char *str)
{
	file->fd = open(str, O_RDONLY);
	if (file->fd == -1)
		return(err_message("open file error\n", FAIL));
	return(process_infile(file));
}

int process_infile(t_file *file)
{
	char	*line;
	int		status;
	
	status = SUCC;
	while(true)
	{
		line = get_next_line(file->fd);
		if (!line)
			break ;
		if (status == SUCC && file->start_map == 0 && *line != '\n' && *line != '\0')
		{
			if(check_dir_fc(file, line) == FAIL)
			{
				status = FAIL;
			}
		}
		else if (status == SUCC && file->start_map == 1 && *line != '\0')
		{
			// printf("Value of line: %s\n", line);
			// printf("Map is%s\n", file->map);
			if(map_read(file, line) == FAIL)
			{
				// printf("We are here\n");
				status = FAIL;
			}
			// printf("Map is%s\n", file->map);
		}
		if(line)
			free(line);
	}
	if (map_check(file) == FAIL)
		status = FAIL;
	printf("Finish reading\n");
	if (status == FAIL || file->no_direc < 6)
		return (FAIL);
	return (SUCC);
}