/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:48:25 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 10:51:56 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static void	ray_step_hori(t_game *game, t_sect *sect, int dof, t_vector step)
{
	int	map_x;
	int	map_y;

	while (dof < game->map_height)
	{
		map_x = (int)(sect->hori.x);
		map_y = (int)(sect->hori.y);
		if (hit_wall(map_x, map_y, game))
			break ;
		else
		{
			sect->hori = v2f_add(sect->hori, step);
			dof++;
		}
	}
}

static void	look_up(t_sect *sect, t_vector *step, float tan_angle, t_player *p)
{
	sect->hori.y = floorf(p->pos.y) - SNAP_FACTOR;
	sect->hori.x = (p->pos.y - sect->hori.y) * tan_angle + p->pos.x;
	step->x = tan_angle;
	step->y = -1.0f;
}

static void	look_down(t_sect *sect, t_vector *step, float tan_angle,
		t_player *p)
{
	sect->hori.y = floorf(p->pos.y) + 1.0f;
	sect->hori.x = (p->pos.y - sect->hori.y) * tan_angle + p->pos.x;
	step->x = -tan_angle;
	step->y = 1.0f;
}

void	get_hori_intersect(t_game *game, t_sect *sect, float player_angle)
{
	t_vector	step;
	t_player	*p;
	int			dof;
	float		tan_angle;

	step = (t_vector){};
	p = game->player;
	dof = 0;
	tan_angle = -1 / tanf(player_angle);
	if (player_angle > PI)
		look_up(sect, &step, tan_angle, p);
	else if (player_angle < PI && player_angle > 0)
		look_down(sect, &step, tan_angle, p);
	else
	{
		sect->hori = v2f_build(p->pos.x, p->pos.y);
		dof = game->map_width;
	}
	ray_step_hori(game, sect, dof, step);
}
