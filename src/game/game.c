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

	float cell_size = WIDTH/game->mapX;
	float y_step = 0;
	float x_step = 0;
	float hx = p->pos.x;
	float hy = p->pos.y;
	float player_angle = p->angle - 30.0f * RAD;
	int map_x;
	int map_y;
	int map_index;

	// casting 60 rays from the player's perspective
	for (int r = 0; r < FOV; r++, player_angle += RAD)
	{
		// NOTE: find horizontal intersection
		int dof = 0;
		float aTan = -1/tanf(player_angle);
		if (player_angle < 0)
			player_angle += 2*PI;
		if (player_angle > 2*PI)
			player_angle -= 2*PI;

		// looking up
		if (player_angle > PI) {
			hy = floorf((float)p->pos.y / cell_size) * cell_size - 0.1f;
			hx = (p->pos.y - hy)*aTan + p->pos.x;
			y_step = -cell_size;
			x_step = -y_step*aTan;
		}
		// looking down
		else if (player_angle < PI && player_angle > 0) {
			hy = floorf(p->pos.y / cell_size) * cell_size + cell_size;
			hx = (p->pos.y - hy)*aTan + p->pos.x;
			y_step = cell_size;
			x_step = -y_step*aTan;
		}
		else
			dof = game->mapX;
		while (dof < game->mapX)
		{
			map_x = (int)(hx/cell_size);
			map_y = (int)(hy/cell_size);
			map_index = map_y * game->mapX + map_x;
			if (map_index > 0 && map_index < game->mapX * game->mapY && game->map[map_index] == 1)
				dof = game->mapX;
			else
			{
				hx += x_step;
				hy += y_step;
				dof++;
			}
		}

		// NOTE: find vertical intersection
		aTan = -tanf(player_angle);
		dof = 0;
		float vx = p->pos.x;
		float vy = p->pos.y;
		// looking right
		if ((player_angle > 3*PI/2 && player_angle < 2*PI) || (player_angle < PI/2 && player_angle > 0))
		{
			vx = floorf(p->pos.x / cell_size) * cell_size + cell_size;
			vy = p->pos.y + (p->pos.x - vx)*aTan;
			x_step = cell_size;
			y_step = -x_step*aTan;
		}
		// looking left
		else if (player_angle > PI/2 && player_angle < 3*PI/2)
		{
			vx = floorf(p->pos.x / cell_size) * cell_size - 0.001f;
			vy = p->pos.y + (p->pos.x - vx)*aTan;
			x_step = -cell_size;
			y_step = -x_step*aTan;
		}
		else
			dof = game->mapX;
		while (dof < game->mapY)
		{
			map_x = (int)(vx/cell_size);
			map_y = (int)(vy/cell_size);
			map_index = map_y * game->mapX + map_x;
			if (map_index > 0 && map_index < game->mapX * game->mapY && map[map_index] == 1)
				dof = game->mapY;
			else
			{
				vx += x_step;
				vy += y_step;
				dof++;
			}
		}

		// calculating distance from player to the intersections
		float distH = v2_sqlen(v2_sub(p->pos, (vector_t){(int)hx, (int)hy}));
		float distV = v2_sqlen(v2_sub(p->pos, (vector_t){(int)vx, (int)vy}));

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
			draw_line(game->image, build_v2(x1, y1), build_v2((int)vx* MINIMAP_SIZE / WIDTH, (int)vy* MINIMAP_SIZE / WIDTH), RED);
		else
			draw_line(game->image, build_v2(x1, y1), build_v2((int)hx* MINIMAP_SIZE / WIDTH, (int)hy* MINIMAP_SIZE / WIDTH), RED);
#endif
		// NOTE: draw wall
		float lineH = (cell_size * WALL_HEIGHT)/corrected_dist;
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
