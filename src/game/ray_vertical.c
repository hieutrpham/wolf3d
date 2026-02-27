/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:51:06 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 10:52:09 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static void	ray_step_vert(t_game *game, t_sect *sect, int dof, t_vector step)
{
	int	map_x;
	int	map_y;

	while (dof < game->map_width)
	{
		map_x = (int)(sect->vert.x);
		map_y = (int)(sect->vert.y);
		if (hit_wall(map_x, map_y, game))
			break ;
		else
		{
			sect->vert = v2f_add(sect->vert, step);
			dof++;
		}
	}
}

static void	look_right(t_sect *sect, t_vector *step, float tan_angle,
		t_player *p)
{
	sect->vert.x = floorf(p->pos.x) + 1.0f;
	sect->vert.y = p->pos.y + (p->pos.x - sect->vert.x) * tan_angle;
	step->x = 1.0f;
	step->y = -tan_angle;
}

static void	look_left(t_sect *sect, t_vector *step, float tan_angle,
		t_player *p)
{
	sect->vert.x = floorf(p->pos.x) - SNAP_FACTOR;
	sect->vert.y = p->pos.y + (p->pos.x - sect->vert.x) * tan_angle;
	step->x = -1.0f;
	step->y = tan_angle;
}

void	get_vert_intersect(t_game *game, t_sect *sect, float player_angle)
{
	t_vector	step;
	t_player	*p;
	int			dof;
	float		tan_angle;

	step = (t_vector){};
	p = game->player;
	dof = 0;
	tan_angle = -tanf(player_angle);
	if ((player_angle > 3 * PI / 2 && player_angle < 2 * PI)
		|| (player_angle < PI / 2 && player_angle > 0))
		look_right(sect, &step, tan_angle, p);
	else if (player_angle > PI / 2 && player_angle < 3 * PI / 2)
		look_left(sect, &step, tan_angle, p);
	else
	{
		sect->vert = v2f_build(p->pos.x, p->pos.y);
		dof = game->map_width;
	}
	ray_step_vert(game, sect, dof, step);
}
