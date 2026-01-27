/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_to_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:43 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 11:40:10 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// void    start_to_display(t_game *game, t_file *files)
// {
//     mlx_set_setting(MLX_STRETCH_IMAGE, 1);
//     game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
//     game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
//     //transfer from files to game
// 	load_textures(game, &files);
//     mlx_image_to_window(game->mlx, game->img, 0, 0);
//     mlx_loop(game->mlx);
// }

// void load_textures(t_game *game, t_file *files)
// {
//     game->tex.no = mlx_load_png(files->no);
//     game->tex.so = mlx_load_png(files->so);
//     game->tex.we = mlx_load_png(files->we);
//     game->tex.ea = mlx_load_png(files->ea);
//     if (!game->tex.no || !game->tex.so || !game->tex.we
//     || !game->tex.ea)
//         err_message("Failed to load texture", FAIL);
// }

void clear_bg(void *param)
{
	t_game *game = param;
	for (uint32_t y = 0; y < game->image->height; y++)
	{
		for (uint32_t x = 0; x < game->image->width; x++)
			put_pixel(game->image, x, y, BG);
	}
}

void draw_map(void *param)
{
	t_game *game = param;
	for (int y = 0; y < game->mapY; y++)
	{
		for (int x = 0; x < game->mapX; x++)
		{
			if (game->map[y*game->mapX + x] == 1)
				draw_rectangle(game->image, (vector_t){x * WIDTH/game->mapX, y * HEIGHT/game->mapY}, WIDTH/game->mapX, HEIGHT/game->mapY, 0x0000ffff);
			draw_line(game->image, (vector_t){x*WIDTH/game->mapX, 0}, (vector_t){x*WIDTH/game->mapX, HEIGHT}, 0x202020ff);
			draw_line(game->image, (vector_t){0, y*HEIGHT/game->mapY}, (vector_t){WIDTH, y*HEIGHT/game->mapY}, 0x202020ff);
		}
	}
}

