/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:25:02 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 11:25:13 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	err_message(char *string, int code)
{
	int		i;
	ssize_t	written;

	i = 0;
	while (string[i])
	{
		written = write(2, &string[i], 1);
		(void)written;
		i++;
	}
	return (code);
}

t_str *str_append(t_str *str, char *line)
{
	int i;

	i = 0;
	if (str->count >= str->cap)
	{
		if (str->cap == 0)
			str->cap = 256;
		else
			str->cap *=2;
		str->str = realloc(str->str, str->cap * sizeof(*str->str));
	}
	while (line[i] != '\n')
		str->str[str->count++] = line[i++];
	return str;
}
