
#include "../include/cube3D.h"

int	parse_no(t_file *file, char *line)
{
	file->no++;
	if (file->no_path && file->no > 1)
		return (err_message("duplicate north direction\n", FAIL));
	file->no_path = check_dir(line, "NO ");
	if (!file->no_path)
		return (err_message("path of north direction error\n", FAIL));
	return (SUCC);
}

int	parse_so(t_file *file, char *line)
{
	file->so++;
	if (file->so_path && file->so > 1)
		return (err_message("duplicate south direction\n", FAIL));
	file->so_path = check_dir(line, "SO ");
	if (!file->so_path)
		return (err_message("path of south direction error\n", FAIL));
	return (SUCC);
}

int	parse_we(t_file *file, char *line)
{
	file->we++;
	if (file->we_path && file->we > 1)
		return (err_message("duplicate west direction\n", FAIL));
	file->we_path = check_dir(line, "WE ");
	if (!file->we_path)
		return (err_message("path of west direction error\n", FAIL));
	return (SUCC);
}

int	parse_ea(t_file *file, char *line)
{
	file->ea++;
	if (file->ea_path && file->ea > 1)
		return (err_message("duplicate east direction\n", FAIL));
	file->ea_path = check_dir(line, "EA ");
	if (!file->ea_path)
		return (err_message("path of east direction error\n", FAIL));
	return (SUCC);
}

char	*check_dir(char *line, char *dir)
{
	int		i;
	int		fd;
	char	*path;

	i = 0 ;
	skip_space(&line);
	if (ft_strncmp(dir, &line[i], 3) == 0)
		return (NULL);
	line += 2;
	skip_space(&line);
	path = get_path(line);
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}
