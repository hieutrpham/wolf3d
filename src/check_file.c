
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
		// if (*line == '\n' || *line == '\0')
		// {
		// 	free(line);
		// 	continue;
		// }
		if (status == SUCC && file->start_map == 0 && *line != '\n' && *line != '\0')
		{
			// printf("line value: %s\n", line);
			if(check_dir_fc(file, line) == FAIL)
			// {
			// 	// free(line);
			// 	// free_file(file);
			// 	printf("Fail here\n");
				status = FAIL;
			// }
			// else
			// 	free(line);	
		}
		// else
		free(line);
	}
	printf("Finish reading\n");
	if (status == FAIL || file->no_direc < 6)
		return (FAIL);
	return (SUCC);
}