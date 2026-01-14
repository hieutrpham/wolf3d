
#include "../include/cube3D.h"

int check_dir_fc(t_file *file, char *line)
{
	if (file->start_map == 0)
	{	
		print_file(file);
		return(parse_dir_fc(file, line));
	}
	return (SUCC);
}

int	parse_dir_fc(t_file *file, char *line)
{
	if (file->no && file->so && file->we && file->ea && file->fl && file->ce
		&& find_wall(line) == SUCC)
		file->start_map = 1;
	if (ft_strncmp(line, "NO ", 3))
		return(parse_no(file, line));
	else if (ft_strncmp(line, "SO ", 3))
		return(parse_so(file, line));
	else if (ft_strncmp(line, "WE ", 3))
		return(parse_we(file, line));
	else if (ft_strncmp(line, "EA ", 3))
		return(parse_ea(file, line));
	else if (ft_strncmp(line, "F ", 2))
		return(parse_floor(file, line));
	else if (ft_strncmp(line, "C ", 2))
		return(parse_ceil(file, line));
	else if (find_wall(line) == FAIL)
		return(err_message("Wrong character before map\n", FAIL));
	else
		return (err_message("Start to read the map\n", SUCC));
}