/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:17:57 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 10:56:22 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

bool	hit_wall(int map_x, int map_y, t_game *game)
{
	return (map_x >= 0 && map_x < game->map_width && map_y >= 0
		&& map_y < game->map_height && game->map[map_y][map_x] == WALL);
}

/* @brief: calculate the intersections of a ray
 * @params: player position vector, angle of the ray direction
 * return: vector containing the coordinate of the intersection
 */
t_sect	cast_ray(t_game *game, float player_angle)
{
	t_sect	sect;

	sect = (t_sect){};
	if (player_angle < 0)
		player_angle += 2 * PI;
	if (player_angle > 2 * PI)
		player_angle -= 2 * PI;
	get_hori_intersect(game, &sect, player_angle);
	get_vert_intersect(game, &sect, player_angle);
	return (sect);
}

void	calc_ray(t_ray *ray)
{
	ray->wall_height = (PROJECTION_DIST) / ray->corrected_dist;
	ray->line_offset = (HEIGHT / 2.0f) - (ray->wall_height / 2.0f);
	ray->uv.origin = (t_vector){ray->r, ray->line_offset};
	ray->uv.height = (int)ray->wall_height;
	ray->r_dir_y = sinf(ray->ray_angle);
	ray->r_dir_x = cosf(ray->ray_angle);
}

void	draw_rays(void *param)
{
	t_game		*game;
	t_player	*p;
	t_ray		ray;

	ray = (t_ray){};
	game = param;
	p = game->player;
	ray.ray_angle = p->angle - 30.0f * RAD;
	while (ray.r < WIDTH)
	{
		ray.sect = cast_ray(game, ray.ray_angle);
		ray.distH = v2i_sqlen(v2f_sub(p->pos, ray.sect.hori));
		ray.distV = v2i_sqlen(v2f_sub(p->pos, ray.sect.vert));
		if (ray.distV > ray.distH)
			ray.dist = sqrtf(ray.distH);
		else
			ray.dist = sqrtf(ray.distV);
		ray.corrected_dist = ray.dist * cosf(ray.ray_angle - p->angle);
		calc_ray(&ray);
		render_texture(ray, game);
		ray.r++;
		ray.ray_angle += game->delta_angle;
	}
}
