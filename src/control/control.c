/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:33:37 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 15:14:41 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static void	handle_key_press(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT)
		game->turn_left = true;
	if (keydata.key == MLX_KEY_RIGHT)
		game->turn_right = true;
	if (keydata.key == MLX_KEY_A)
		game->left = true;
	if (keydata.key == MLX_KEY_D)
		game->right = true;
	if (keydata.key == MLX_KEY_W)
		game->forward = true;
	if (keydata.key == MLX_KEY_S)
		game->backward = true;
	if (keydata.key == MLX_KEY_M)
		game->mouse_enabled = !game->mouse_enabled;
}

static void	handle_key_release(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT)
		game->turn_left = false;
	if (keydata.key == MLX_KEY_RIGHT)
		game->turn_right = false;
	if (keydata.key == MLX_KEY_A)
		game->left = false;
	if (keydata.key == MLX_KEY_D)
		game->right = false;
	if (keydata.key == MLX_KEY_W)
		game->forward = false;
	if (keydata.key == MLX_KEY_S)
		game->backward = false;
}

void	key_control(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS)
		handle_key_press(game, keydata);
	if (keydata.action == MLX_RELEASE)
		handle_key_release(game, keydata);
}
