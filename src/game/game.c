/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:47:55 by trupham           #+#    #+#             */
/*   Updated: 2026/01/31 17:56:01 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void draw_rays(void *param)
{
	t_game *game = param;
	t_player *p = game->player;
	float dist;
	float player_angle = p->angle - 30.0f * RAD;

	for (int r = 0; r < WIDTH; r++, player_angle += FOV*RAD/WIDTH)
	{
		if (player_angle == PI || player_angle == PI/2 || player_angle == 3*PI/2 || player_angle == 2*PI)
			player_angle += 0.0001f;
		t_sect sect = cast_ray(game, player_angle);
		// printf("%f %f %f %f\n", sect.hori.x, sect.hori.y, sect.vert.x, sect.vert.y);
		// calculating distance from player to the intersections
		float distH = v2i_sqlen(v2i_sub(p->pos, sect.hori));
		float distV = v2i_sqlen(v2i_sub(p->pos, sect.vert));

		if (distV > distH)
			dist = sqrtf(distH);
		else
			dist = sqrtf(distV);
		float corrected_dist = dist * cosf(player_angle - p->angle);

		// draw rays vision in minimap
		// int x1 = (int)p->pos.x * MINIMAP_SIZE / WIDTH;
		// int y1 = (int)p->pos.y * MINIMAP_SIZE / WIDTH;
		// if ( distH > distV)
		// 	draw_line(game->image, v2i_build(x1, y1), v2i_build((int)sect.vert.x * MINIMAP_SIZE / WIDTH, (int)sect.vert.y * MINIMAP_SIZE / WIDTH), RED);
		// else
		// 	draw_line(game->image, v2i_build(x1, y1), v2i_build((int)sect.hori.x * MINIMAP_SIZE / WIDTH, (int)sect.hori.y * MINIMAP_SIZE / WIDTH), RED);

		// 3D projection.
		// TODO: texture drawing
		float lineH = (WALL_HEIGHT)/corrected_dist;
		if (lineH > HEIGHT)
			lineH = HEIGHT;
		float line_offset = (HEIGHT/2.0f) - (lineH/2.0f);
		t_vector origin = {r, line_offset};
		// printf("%f\n", fmod(sect.hori.x, 1.0)*game->we->width);
		uint color = get_pixel_from_texture(game->we, distV > distH ? (int)(fmod(sect.hori.x, 1.0)*game->we->width): (int)(fmod(sect.vert.y, 1.0)*game->we->width), 300);

		draw_strip(game->image, origin, (int)lineH, set_brightness(color, lineH/BRIGHTNESS));
		// draw_strip(game->image, origin, (int)lineH, set_brightness(RED, lineH/BRIGHTNESS));
	}
}

void game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx, clear_bg, game);
	mlx_loop_hook(game->mlx, draw_rays, game);
	mlx_loop_hook(game->mlx, draw_map, game);
}

int player_init(t_game *game)
{
	game->player = malloc(sizeof(*game->player));
	if (!game->player)
		return FAIL;
	game->player->angle = PI/4;
	game->player->pos.x = 2.0f;
	game->player->pos.y = 2.0f;
	game->player->dx = cosf(game->player->angle) * 0.1f;
	game->player->dy = sinf(game->player->angle) * 0.1f;
	return SUCC;
}

int game_init(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game->mlx)
		return FAIL;
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return FAIL;
	game->we = mlx_load_png("./textures/WE.png");

	// for (uint ti = 0; ti < game->we->width * game->we->height; ti++)
	// 	printf("%x\n", get_color(game->we->pixels[ti], game->we->pixels[ti+1], game->we->pixels[ti+2], game->we->pixels[ti+3]));
	game->map = map;
	game->mapX = 8;
	game->mapY = 8;
	player_init(game);
	return SUCC;
}
