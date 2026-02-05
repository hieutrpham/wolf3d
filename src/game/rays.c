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
	return (map_index >= 0 && map_index < game->mapX * game->mapY
		&& game->map[map_index] != 0);
}

// stepping the ray in the horizontal direction
void ray_step_hori(t_game *game, t_sect *sect, int dof, t_vector step)
{
	int map_x;
	int map_y;

	while (dof < game->mapX)
	{
		map_x = (int)(sect->hori.x);
		map_y = (int)(sect->hori.y);
		int map_index = map_y * game->mapX + map_x;
		if (hit_wall(map_index, game))
			break;
		else
		{
			sect->hori.x += step.x;
			sect->hori.y += step.y;
			dof++;
		}
	}
}

// stepping the ray in the vertical direction
void ray_step_vert(t_game *game, t_sect *sect, int dof, t_vector step)
{
	int map_x;
	int map_y;

	while (dof < game->mapX)
	{
		map_x = (int)(sect->vert.x);
		map_y = (int)(sect->vert.y);
		int map_index = map_y * game->mapX + map_x;
		if (hit_wall(map_index, game))
			break;
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
	t_vector step = {};
	t_player *p = game->player;
	int dof = 0;
	float aTan = -1/tanf(player_angle);

	// looking up
	if (player_angle > PI) {
		sect->hori.y = floorf(p->pos.y) - 0.0001f;
		sect->hori.x = (p->pos.y - sect->hori.y)*aTan + p->pos.x;
		step.y = -1.0f;
		step.x = aTan;
	}
	// looking down
	else if (player_angle < PI && player_angle > 0) {
		sect->hori.y = floorf(p->pos.y) + 1.0f;
		sect->hori.x = (p->pos.y - sect->hori.y)*aTan + p->pos.x;
		step.y = 1.0f;
		step.x = -aTan;
	}
	else
	{
		sect->hori.x = p->pos.x;
		sect->hori.y = p->pos.y;
		dof = game->mapX;
	}
	ray_step_hori(game, sect, dof, step);
}

void get_vert_intersect(t_game *game, t_sect *sect, float player_angle)
{
	t_vector step = {};
	t_player *p = game->player;
	int dof = 0;
	float aTan = -tanf(player_angle);

	if ((player_angle > 3*PI/2 && player_angle < 2*PI) || (player_angle < PI/2 && player_angle > 0))
	{
		sect->vert.x = floorf(p->pos.x) + 1.0f;
		sect->vert.y = p->pos.y + (p->pos.x - sect->vert.x)*aTan;
		step.x = 1.0f;
		step.y = -step.x*aTan;
	}
	// looking left
	else if (player_angle > PI/2 && player_angle < 3*PI/2)
	{
		sect->vert.x = floorf(p->pos.x) - 0.0001f;
		sect->vert.y = p->pos.y + (p->pos.x - sect->vert.x)*aTan;
		step.x = -1.0f;
		step.y = -step.x*aTan;
	}
	else
	{
		sect->vert.x = p->pos.x;
		sect->vert.y = p->pos.y;
		dof = game->mapX;
	}
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
