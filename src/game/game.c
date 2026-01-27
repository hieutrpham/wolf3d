/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:47:55 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 13:48:04 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,1,0,0,1,
	1,0,1,0,1,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

// void draw_rays(void *param)
// {
// 	t_player *p = param;
// }

void game_loop(t_game *game)
{
	// mlx_loop_hook(mlx, draw_circle, mlx);
	// mlx_loop_hook(game->mlx, clear_bg, NULL);
	mlx_loop_hook(game->mlx, draw_map, game);
	// mlx_loop_hook(mlx, draw_rays, &player);
}

int game_init(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->map = map;
	game->mapX = 8;
	game->mapY = 8;
	if (!game->mlx)
		return 1;
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return 1;
	return 0;
}

