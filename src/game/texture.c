/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:22:42 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 13:54:49 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	render_texture(t_ray ray, t_game *game)
{
	if (ray.dist_vert > ray.dist_hori && ray.r_dir_y < 0)
	{
		ray.uv.tx = (int)(fmod(ray.sect.hori.x, 1.0) * game->so->width);
		draw_texture(game, ray.uv, SO);
	}
	else if (ray.dist_vert > ray.dist_hori && ray.r_dir_y > 0)
	{
		ray.uv.tx = (int)(fmod(ray.sect.hori.x, 1.0) * game->no->width);
		draw_texture(game, ray.uv, NO);
	}
	else if (ray.dist_vert < ray.dist_hori && ray.r_dir_x > 0)
	{
		ray.uv.tx = (int)(fmod(ray.sect.vert.y, 1.0) * game->ea->width);
		draw_texture(game, ray.uv, EA);
	}
	else if (ray.dist_vert < ray.dist_hori && ray.r_dir_x < 0)
	{
		ray.uv.tx = (int)(fmod(ray.sect.vert.y, 1.0) * game->we->width);
		draw_texture(game, ray.uv, WE);
	}
}

bool	load_texture(t_game *game, t_file *file)
{
	game->we = mlx_load_png(file->we_path);
	if (!game->we)
		return (false);
	game->no = mlx_load_png(file->no_path);
	if (!game->no)
		return (false);
	game->ea = mlx_load_png(file->ea_path);
	if (!game->ea)
		return (false);
	game->so = mlx_load_png(file->so_path);
	if (!game->so)
		return (false);
	return (true);
}

void	unload_textures(t_game *game)
{
	if (game->we)
		mlx_delete_texture(game->we);
	if (game->no)
		mlx_delete_texture(game->no);
	if (game->ea)
		mlx_delete_texture(game->ea);
	if (game->so)
		mlx_delete_texture(game->so);
}
