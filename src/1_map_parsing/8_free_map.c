
#include "../include/cube3D.h"

void	clear_previous(char **str, int len)
{
	int	i;

	if (!str || !str[0])
		return ;
	i = 0;
	while (i < len)
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}
