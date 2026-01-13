/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:28:46 by trupham           #+#    #+#             */
/*   Updated: 2025/12/13 12:12:10 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

int main(int argc, char *argv[])
{
	t_file	file;
	
	if (argc != 2)
		return (err_message("Usage: ./cub3D <map.cub>\n", FAIL));
	if (check_exter(argv[1]) == FAIL)
		return (err_message("map is wrong\n", FAIL));
	ft_bzero(&file, sizeof(t_file));
	// file.fl = 1;
	// file.ce = 1;
	if(check_inter(&file, argv[1]) == FAIL)
		return (FAIL);
	return (SUCC);
}

