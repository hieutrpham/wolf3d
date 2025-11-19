
#include "cube3D.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (err_message("Usage: ./cub3D <map.cub>\n", FAIL));
	if (check_file(argv[1]) == FAIL)
		return (err_message("map is wrong\n", FAIL));
	printf("Start to load map\n");
	return (SUCC);
}

int	err_message(char *string, int code)
{
	int	i;

	i = 0;
	while (string[i])
	{
		write(2, &string[i], 1);
		i++;
	}
	return (code);
}

int check_file(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '.' && str[i])
		i++;
	if (ft_strcmp(&str[i + 1], "cub") == 0 && (str[i + 4] == '\0'))
		return (SUCC);
	return (FAIL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1); // this is wrong
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}