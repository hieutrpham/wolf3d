/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_free_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:03:34 by trupham           #+#    #+#             */
/*   Updated: 2026/02/16 11:03:37 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
