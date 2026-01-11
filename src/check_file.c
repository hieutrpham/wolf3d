
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

int check_inter(char *str)
{
	int 	fd;
	int		res[6];
	char 	*map;
	int		result;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return(err_message("open file error\n", FAIL));
	map = ft_strdup("");
	if (!map)
		return(clean_up(NULL, NULL, fd, FAIL));
	ft_bzero(res, sizeof(res));
	result = process_infile(fd, &map, res);
	if (result == FAIL)
		return(clean_up(map, NULL, fd, FAIL));
	// if(check_map(map) == FAIL)
	// 	return(clean_up(map, NULL, fd, FAIL));
	return(clean_up(map, NULL, fd, SUCC));
}

int process_infile(int fd, char **map, int *res)
{
	char	*line;
	char	*map_temp;
	
	while(true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n' || *line == '\0')
		{
			free(line);
			continue;
		}
		if(check_first(line, res) == FAIL)
			return(clean_up(NULL, line, 0, FAIL));
		map_temp = ft_strjoin(*map, line);
		if (!map_temp)
			return(clean_up(NULL, line, 0, FAIL));
		free(*map);
		free(line);
		*map = map_temp;
	}
	return (SUCC);
}