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
	1,0,0,0,1,0,0,1,
	1,0,1,0,1,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void draw_rays(void *param)
{
	t_game *game = param;
	t_player *p = game->player;

	float player_angle = p->angle - 30.0f * RAD;

	// casting 60 rays from the player's perspective
	for (int r = 0; r < FOV; r++, player_angle += RAD)
	{
		t_sect sect = cast_ray(game, player_angle);
		// calculating distance from player to the intersections
		float distH = v2_sqlen(v2_sub(p->pos, (t_vector){(int)sect.hx, (int)sect.hy}));
		float distV = v2_sqlen(v2_sub(p->pos, (t_vector){(int)sect.vx, (int)sect.vy}));

		float dist;
		if (distV > distH)
			dist = sqrtf(distH);
		else
			dist = sqrtf(distV);
		float corrected_dist = dist * cosf(player_angle - p->angle);

#if 1
		int x1 = (int)p->pos.x * MINIMAP_SIZE / WIDTH;
		int y1 = (int)p->pos.y * MINIMAP_SIZE / WIDTH;
		if ( distH > distV)
			draw_line(game->image, build_v2(x1, y1), build_v2((int)sect.vx* MINIMAP_SIZE / WIDTH, (int)sect.vy* MINIMAP_SIZE / WIDTH), RED);
		else
			draw_line(game->image, build_v2(x1, y1), build_v2((int)sect.hx* MINIMAP_SIZE / WIDTH, (int)sect.hy* MINIMAP_SIZE / WIDTH), RED);
#endif
		// NOTE: draw wall
		float lineH = (WIDTH * WALL_HEIGHT/game->mapX)/corrected_dist;
		if (lineH > HEIGHT)
			lineH = HEIGHT;
		float line_offset = (HEIGHT/2.0f) - (lineH/2.0f);
		if (distV > distH)
			draw_rectangle(game->image, build_v2(r*game->image->width/FOV, (int)line_offset), game->image->width/FOV, (int)lineH, 0x90E0EFff);
		else
			draw_rectangle(game->image, build_v2(r*game->image->width/FOV, (int)line_offset), game->image->width/FOV, (int)lineH, 0x48CAE4ff);
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
	game->player->angle = PI/3;
	game->player->pos.x = 300;
	game->player->pos.y = 300;
	game->player->dx = cosf(game->player->angle);
	game->player->dy = sinf(game->player->angle);
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
	game->map = map;
	game->mapX = 8;
	game->mapY = 8;
	player_init(game);
	return SUCC;
}
