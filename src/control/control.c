/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:33:37 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 11:33:55 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	key_control(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_A)
		game->player->angle -= 0.1f;
	if (keydata.key == MLX_KEY_D)
		game->player->angle += 0.1f;
	if (keydata.key == MLX_KEY_W)
		game->player->pos = v2_add(game->player->pos, (vector_t){1, 1});
	if (keydata.key == MLX_KEY_S)
		game->player->pos = v2_sub(game->player->pos, (vector_t){1, 1});
}

