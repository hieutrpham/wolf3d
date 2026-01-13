
#include "../include/cube3D.h"

char *get_path(char *line)
{
	char	*out;
	int		len;
	int		i;

	len = ft_strlen(line);
	out = malloc(len);
	if(!out)
		return (NULL);
	i = 0;
	while(line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
	{
		out[i] = line[i];
		i++;
	}
	out[i] = '\0';
	return out;
}

void skip_space(char **str)
{
	while(**str == ' ')
		(*str)++;
}