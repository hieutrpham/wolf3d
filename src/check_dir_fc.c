
#include "../include/cube3D.h"

int check_dir_fc(t_file *file, char *line)
{
	if (file->no > 1 || file->so > 1 || file->we > 1 || file->ea > 1 || file->fl > 1 || file->ce > 1 )
		return(err_message("duplicate direction\n", FAIL));
	if (file->start_map == 0)
		parse_dir_fc(file, line);
	if (file->no && file->so && file->we && file->ea && file->fl && file->ce)
		file->start_map = 1;
	print_file(file);
	return (SUCC);
}

void print_file(t_file *file)
{
	printf("Value of path: %s\n %s\n %s\n %s\n", file->no_path, file->so_path, file->we_path, file->ea_path);
	printf("Value of direction: %d %d %d %d %d %d\n", file->no, file->so, file->we, file->ea, file->fl, file->ce);
	printf("Value of floor color: %d %d %d\n", file->fl_rgb[0], file->fl_rgb[1], file->fl_rgb[2]);
	printf("Value of ceiling color: %d %d %d\n", file->ce_rgb[0], file->ce_rgb[1], file->ce_rgb[2]);
}

void	parse_dir_fc(t_file *file, char *line)
{
		file->no_path = check_dir(line, "NO ");
		if (file->no_path)
			file->no++;
		file->so_path = check_dir(line, "SO ");
		if (file->so_path)
			file->so++;
		file->we_path = check_dir(line, "WE ");
		if (file->we_path)
			file->we++;
		file->ea_path = check_dir(line, "EA ");
		if (file->ea_path)
			file->ea++;
		if (check_fc(file, line, "F ") == SUCC)
			file->fl++;
		if (check_fc(file, line, "C ") == SUCC)
			file->ce++;
		file->no_direc = file->no + file->so + file->we + file->ea
		+ file->fl + file->ce;
}
char *check_dir(char *line, char *dir)
{
	int		i;
	int		fd;
	char 	*path;

	i = 0 ;
	skip_space(&line);
	if (ft_strncmp(dir, &line[i], 3) == 0)
		return (NULL);
	line += 2;
	skip_space(&line);
	path = get_path(line);
	if (!path)
	{
		printf("path of direction error\n");
		return(NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		printf("path of direction error\n");
		return(NULL);
	}
	close(fd);
	return (path);
}


