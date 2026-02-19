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
