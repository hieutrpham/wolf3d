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
