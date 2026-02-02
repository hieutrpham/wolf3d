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
		&& game->map[map_index] == 1);
}

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
			dof = game->mapX;
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
			dof = game->mapX;
		else
		{
			sect->vert.x += step.x;
			sect->vert.y += step.y;
			dof++;
		}
	}
}

/* @brief: calculate the intersections of a ray
* @params: player position vector, angle of the ray direction
* return: vector containing the coordinate of the intersection
*/
t_sect cast_ray(t_game *game, float player_angle)
{
	t_player *p = game->player;
	t_sect sect = {};

	float y_step = 0;
	float x_step = 0;

	// NOTE: find horizontal intersection
	int dof = 0;
	float aTan = -1/tanf(player_angle);
	if (player_angle < 0)
		player_angle += 2*PI;
	if (player_angle > 2*PI)
		player_angle -= 2*PI;

	float cell_size = WIDTH/game->mapY;
	// looking up
	if (player_angle > PI) {
		sect.hori.y = floorf((float)p->pos.y / cell_size) * cell_size - 0.1f;
		sect.hori.x = (p->pos.y - sect.hori.y)*aTan + p->pos.x;
		y_step = -cell_size;
		x_step = -y_step*aTan;
	}
	// looking down
	else if (player_angle < PI && player_angle > 0) {
		sect.hori.y = floorf(p->pos.y / cell_size) * cell_size + cell_size;
		sect.hori.x = (p->pos.y - sect.hori.y)*aTan + p->pos.x;
		y_step = cell_size;
		x_step = -y_step*aTan;
	}
	else
		dof = game->mapX;
	t_vector2f step = {x_step, y_step};
	ray_step_hori(game, &sect, dof, step);

	// find vertical intersection
	// cell_size = WIDTH/game->mapX;
	aTan = -tanf(player_angle);
	dof = 0;
	sect.vert.x = p->pos.x;
	sect.vert.y = p->pos.y;
	// looking right
	if ((player_angle > 3*PI/2 && player_angle < 2*PI) || (player_angle < PI/2 && player_angle > 0))
	{
		sect.vert.x = floorf(p->pos.x / cell_size) * cell_size + cell_size;
		sect.vert.y = p->pos.y + (p->pos.x - sect.vert.x)*aTan;
		x_step = cell_size;
		y_step = -x_step*aTan;
	}
	// looking left
	else if (player_angle > PI/2 && player_angle < 3*PI/2)
	{
		sect.vert.x = floorf(p->pos.x / cell_size) * cell_size - 0.001f;
		sect.vert.y = p->pos.y + (p->pos.x - sect.vert.x)*aTan;
		x_step = -cell_size;
		y_step = -x_step*aTan;
	}
	else
		dof = game->mapX;

	step.x = x_step;
	step.y = y_step;
	// stepping by x, y_step until hitting a wall or dof is equal to the map's size. assumption is that the map is always closed off
	ray_step_vert(game, &sect, dof, step);
	return sect;
}
