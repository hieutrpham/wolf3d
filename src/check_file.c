
#include "../include/cube3D.h"

int check_exter(char *str)
{
	int len;

	if (!str)
		return (FAIL);
	len = ft_strlen(str);
	if (len < 4)
		return (FAIL);
	if (str[len - 4] != '.')
        return (FAIL);
	if (ft_strcmp(str + len - 3, "cub") == 0)
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
				status = FAIL;
		}
		else if (status == SUCC && file->start_map == 1 && *line != '\0')
		{
			if(map_read(file, line) == FAIL)
				status = FAIL;
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