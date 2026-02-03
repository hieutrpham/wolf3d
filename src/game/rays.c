/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:17:57 by trupham           #+#    #+#             */
/*   Updated: 2026/01/31 23:13:32 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

bool hit_wall(int map_index, t_game *game)
{
	return (map_index > 0 && map_index < game->mapX * game->mapY
		&& game->map[map_index] != 0);
}

static const uint color[] = {
	0x979aa1ff,
	0x09a630FF,
	0x84cc16FF,
	0xf1c915FF,
	0xda5a00ff,
};
// stepping the ray in the horizontal direction
void ray_step_hori(t_game *game, t_sect *sect, int dof, t_vector2f step)
{
	int map_x;
	int map_y;
	float cell_size = WIDTH/game->mapX;

	while (dof < game->mapX)
	{
		map_x = (int)(sect->hori.x/cell_size);
		map_y = (int)(sect->hori.y/cell_size);
		int map_index = map_y * game->mapX + map_x;
		if (hit_wall(map_index, game))
		{
			sect->color = color[game->map[map_index] - 1];
			break;
		}
		else
		{
			sect->hori.x += step.x;
			sect->hori.y += step.y;
			dof++;
		}
	}
}

// stepping the ray in the vertical direction
void ray_step_vert(t_game *game, t_sect *sect, int dof, t_vector2f step)
{
	int map_x;
	int map_y;
	float cell_size = WIDTH/game->mapX;

	while (dof < game->mapX)
	{
		map_x = (int)(sect->vert.x/cell_size);
		map_y = (int)(sect->vert.y/cell_size);
		int map_index = map_y * game->mapX + map_x;
		if (hit_wall(map_index, game))
		{
			sect->color = color[game->map[map_index] - 1];
			dof = game->mapX;
		}
		else
		{
			sect->vert.x += step.x;
			sect->vert.y += step.y;
			dof++;
		}
	}
}

void get_hori_intersect(t_game *game, t_sect *sect, float player_angle)
{
	t_vector2f step = {};
	t_player *p = game->player;
	int dof = 0;
	float aTan = -1/tanf(player_angle);

	float cell_size = WIDTH/game->mapY;
	// looking up
	if (player_angle > PI) {
		sect->hori.y = floorf((float)p->pos.y / cell_size) * cell_size - 0.1f;
		sect->hori.x = (p->pos.y - sect->hori.y)*aTan + p->pos.x;
		step.y = -cell_size;
		step.x = -step.y*aTan;
	}
	// looking down
	else if (player_angle < PI && player_angle > 0) {
		sect->hori.y = floorf(p->pos.y / cell_size) * cell_size + cell_size;
		sect->hori.x = (p->pos.y - sect->hori.y)*aTan + p->pos.x;
		step.y = cell_size;
		step.x = -step.y*aTan;
	}
	else
		dof = game->mapX;
	ray_step_hori(game, sect, dof, step);
}

void get_vert_intersect(t_game *game, t_sect *sect, float player_angle)
{
	t_vector2f step = {};
	t_player *p = game->player;
	int dof = 0;
	float aTan = -tanf(player_angle);
	float cell_size = WIDTH/game->mapY;

	if ((player_angle > 3*PI/2 && player_angle < 2*PI) || (player_angle < PI/2 && player_angle > 0))
	{
		sect->vert.x = floorf(p->pos.x / cell_size) * cell_size + cell_size;
		sect->vert.y = p->pos.y + (p->pos.x - sect->vert.x)*aTan;
		step.x = cell_size;
		step.y = -step.x*aTan;
	}
	// looking left
	else if (player_angle > PI/2 && player_angle < 3*PI/2)
	{
		sect->vert.x = floorf(p->pos.x / cell_size) * cell_size - 0.001f;
		sect->vert.y = p->pos.y + (p->pos.x - sect->vert.x)*aTan;
		step.x = -cell_size;
		step.y = -step.x*aTan;
	}
	else
		dof = game->mapX;
	ray_step_vert(game, sect, dof, step);
}

/* @brief: calculate the intersections of a ray
* @params: player position vector, angle of the ray direction
* return: vector containing the coordinate of the intersection
*/
t_sect cast_ray(t_game *game, float player_angle)
{
	t_sect sect = {};

	if (player_angle < 0)
		player_angle += 2*PI;
	if (player_angle > 2*PI)
		player_angle -= 2*PI;

	get_hori_intersect(game, &sect, player_angle);
	get_vert_intersect(game, &sect, player_angle);
	return sect;
}
