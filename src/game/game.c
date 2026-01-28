/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:47:55 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 16:19:44 by trupham          ###   ########.fr       */
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
	float yo, xo;
	float ra = p->angle - 30.0f * DR;
	for (int r = 0; r < 60; r++, ra += DR)
	{
		int dof = 0;
		float aTan = -1/tanf(ra);
		float hx, hy;
		if (ra < 0)
			ra += 2*PI;
		if (ra > 2*PI)
			ra -= 2*PI;
		// float distH = 1e9;
		// NOTE: find horizontal intersection
		// looking up
		if (ra > PI) {
			hy = floorf((float)p->pos.y / (float)cell_size) * (float)cell_size - 0.001f;
			hx = (p->pos.y - hy)*aTan + p->pos.x;
			yo = (float)cell_size * -1.;
			xo = -yo*aTan;
		}
		// looking down
		else if (ra < PI && ra > 0) {
			hy = floorf(p->pos.y / cell_size) * cell_size + cell_size;
			hx = (p->pos.y - hy)*aTan + p->pos.x;
			yo = cell_size;
			xo = -yo*aTan;
		}
		else {
			hx = p->pos.x;
			hy = p->pos.y;
			dof = game->mapX;
		}
		while (dof < game->mapX)
		{
			int mx = (int)(hx/cell_size);
			int my = (int)(hy/cell_size);
			int mp = my * game->mapX + mx;
			if (mp > 0 && mp < game->mapX * game->mapY && game->map[mp] == 1)
				dof = game->mapX;
			else
			{
				hx += xo;
				hy += yo;
				dof++;
			}
		}
		// NOTE: find vertical intersection
		aTan = -tanf(ra);
		dof = 0;
		float vx = p->pos.x, vy = p->pos.y;
		// looking right
		if ((ra > 3*PI/2 && ra < 2*PI) || (ra < PI/2 && ra > 0))
		{
			vx = floorf(p->pos.x / cell_size) * cell_size + cell_size;
			vy = p->pos.y + (p->pos.x - vx)*aTan;
			xo = cell_size;
			yo = -xo*aTan;
		}
		// looking left
		else if (ra > PI/2 && ra < 3*PI/2)
		{
			vx = floorf(p->pos.x / cell_size) * cell_size - 0.001f;
			vy = p->pos.y + (p->pos.x - vx)*aTan;
			xo = -cell_size;
			yo = -xo*aTan;
		}
		else {
			vx = p->pos.x;
			vy = p->pos.y;
			dof = game->mapX;
		}
		while (dof < game->mapX)
		{
			int mx = (int)(vx/cell_size);
			int my = (int)(vy/cell_size);
			int mp = my * game->mapX + mx;
			if (mp > 0 && mp < game->mapX * game->mapY && map[mp] == 1)
				dof = game->mapX;
			else
			{
				vx += xo;
				vy += yo;
				dof++;
			}
		}

		float distH = (hy - p->pos.y)*(hy - p->pos.y) + (hx - p->pos.x)*(hx - p->pos.x);
		float distV = (vy - p->pos.y)*(vy - p->pos.y) + (vx - p->pos.x)*(vx - p->pos.x);
		float dist = distV > distH ? distH : distV;
		dist = sqrtf(dist);
		float corrected_dist = dist * cosf(ra - p->angle);

		// TODO: implement minimap
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
		draw_rectangle(game->image, build_v2(r*game->image->width/(int)FOV, (int)line_offset), game->image->width/(int)FOV, (int)lineH, GREEN);
	}
}

void game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx, clear_bg, game);
	mlx_loop_hook(game->mlx, draw_map, game);
	mlx_loop_hook(game->mlx, draw_rays, game);
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
	game->player = malloc(sizeof(*game->player));
	if (!game->player)
		return FAIL;
	game->player->angle = PI/2;
	game->player->pos.x = game->image->width/2;
	game->player->pos.y = game->image->height/2;

	return 0;
}

