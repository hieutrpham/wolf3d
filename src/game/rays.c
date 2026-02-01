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

/* @brief: calculate the intersections of a ray
* @params: player position vector, angle of the ray direction
* return: vector containing the coordinate of the intersection
*/

t_sect cast_ray(t_game *game, float player_angle)
{
	t_player *p = game->player;
	t_sect sect = {};

	int map_x;
	int map_y;
	int map_index;
	float y_step = 0;
	float x_step = 0;
	float cell_size = WIDTH/game->mapX;

	// NOTE: find horizontal intersection
	int dof = 0;
	float aTan = -1/tanf(player_angle);
	if (player_angle < 0)
		player_angle += 2*PI;
	if (player_angle > 2*PI)
		player_angle -= 2*PI;

	// looking up
	if (player_angle > PI) {
		sect.hy = floorf((float)p->pos.y / cell_size) * cell_size - 0.1f;
		sect.hx = (p->pos.y - sect.hy)*aTan + p->pos.x;
		y_step = -cell_size;
		x_step = -y_step*aTan;
	}
	// looking down
	else if (player_angle < PI && player_angle > 0) {
		sect.hy = floorf(p->pos.y / cell_size) * cell_size + cell_size;
		sect.hx = (p->pos.y - sect.hy)*aTan + p->pos.x;
		y_step = cell_size;
		x_step = -y_step*aTan;
	}
	else
	dof = game->mapX;
	while (dof < game->mapX)
	{
		map_x = (int)(sect.hx/cell_size);
		map_y = (int)(sect.hy/cell_size);
		map_index = map_y * game->mapX + map_x;
		if (map_index > 0 && map_index < game->mapX * game->mapY && game->map[map_index] == 1)
			dof = game->mapX;
		else
		{
			sect.hx += x_step;
			sect.hy += y_step;
			dof++;
		}
	}

	// NOTE: find vertical intersection
	aTan = -tanf(player_angle);
	dof = 0;
	sect.vx = p->pos.x;
	sect.vy = p->pos.y;
	// looking right
	if ((player_angle > 3*PI/2 && player_angle < 2*PI) || (player_angle < PI/2 && player_angle > 0))
	{
		sect.vx = floorf(p->pos.x / cell_size) * cell_size + cell_size;
		sect.vy = p->pos.y + (p->pos.x - sect.vx)*aTan;
		x_step = cell_size;
		y_step = -x_step*aTan;
	}
	// looking left
	else if (player_angle > PI/2 && player_angle < 3*PI/2)
	{
		sect.vx = floorf(p->pos.x / cell_size) * cell_size - 0.001f;
		sect.vy = p->pos.y + (p->pos.x - sect.vx)*aTan;
		x_step = -cell_size;
		y_step = -x_step*aTan;
	}
	else
	dof = game->mapX;
	while (dof < game->mapY)
	{
		map_x = (int)(sect.vx/cell_size);
		map_y = (int)(sect.vy/cell_size);
		map_index = map_y * game->mapX + map_x;
		if (map_index > 0 && map_index < game->mapX * game->mapY && game->map[map_index] == 1)
			dof = game->mapY;
		else
		{
			sect.vx += x_step;
			sect.vy += y_step;
			dof++;
		}
	}
	return sect;
}
