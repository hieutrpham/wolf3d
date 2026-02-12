/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:47:55 by trupham           #+#    #+#             */
/*   Updated: 2026/02/06 14:55:42 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void draw_rays(void *param)
{
	t_game *game = param;
	t_player *p = game->player;
	float dist;
	float ray_angle = p->angle - 30.0f * RAD;

	for (int r = 0; r < WIDTH; r++, ray_angle += FOV*RAD/WIDTH)
	{
		if (ray_angle == PI || ray_angle == PI/2
			|| ray_angle == 3*PI/2 || ray_angle == 2*PI)
			ray_angle += 0.0001f;
		t_sect sect = cast_ray(game, ray_angle);
		float distH = v2i_sqlen(v2f_sub(p->pos, sect.hori));
		float distV = v2i_sqlen(v2f_sub(p->pos, sect.vert));

		if (distV > distH)
			dist = sqrtf(distH);
		else
			dist = sqrtf(distV);
		float corrected_dist = dist * cosf(ray_angle - p->angle);

		// 3D projection.
		float lineH = (WALL_HEIGHT)/corrected_dist;
		float line_offset = (HEIGHT/2.0f) - (lineH/2.0f);
		t_vector origin = {r, line_offset};
		t_uvmap uv = {
			.origin = origin,
			.height = (int)lineH,
			.tx = 0,
		};
		float r_dir_y = sinf(ray_angle);
		float r_dir_x = cosf(ray_angle);
		// ray hits horizontal and opposite the y axis
		if (distV > distH && r_dir_y < 0)
		{
			uv.tx = (int)(fmod(sect.hori.x, 1.0)*game->so->width);
			draw_texture(game, uv, SO);
		}
		// ray hits horizontal and same direction with the y axis
		else if (distV > distH && r_dir_y > 0)
		{
			uv.tx = (int)(fmod(sect.hori.x, 1.0)*game->no->width);
			draw_texture(game, uv, NO);
		}
		// ray hits vertical and same direction with the x axis
		else if (distV < distH && r_dir_x > 0)
		{
			uv.tx = (int)(fmod(sect.vert.y, 1.0)*game->ea->width);
			draw_texture(game, uv, EA);
		}
		else if (distV < distH && r_dir_x < 0)
		{
			uv.tx = (int)(fmod(sect.vert.y, 1.0)*game->we->width);
			draw_texture(game, uv, WE);
		}
	}
}

void fps_hook(void* param)
{
	t_game* game;
	double current_time;
	double delta_time;

	game = param;
	current_time = mlx_get_time();
	delta_time = current_time - game->last_time;
	game->last_time = current_time;
	game->delta_time = delta_time;
}

void game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx, fps_hook, game);
	mlx_loop_hook(game->mlx, clear_bg, game);
	mlx_loop_hook(game->mlx, render_ceiling, game);
	mlx_loop_hook(game->mlx, render_floor, game);
	mlx_loop_hook(game->mlx, draw_rays, game);
	// mlx_loop_hook(game->mlx, draw_map, game);
}

int player_init(t_game *game, t_file *file)
{
	game->player = malloc(sizeof(*game->player));
	if (!game->player)
		return FAIL;
	if (file->player_dir == 'N')
		game->player->angle = 3*PI/2;
	if (file->player_dir == 'E')
		game->player->angle = PI;
	if (file->player_dir == 'W')
		game->player->angle = 2*PI;
	if (file->player_dir == 'S')
		game->player->angle = PI/2;

	game->player->pos.x = file->player_x + 0.5f;
	game->player->pos.y = file->player_y + 0.5f;
	game->player->dir.x = cosf(game->player->angle) * 0.1f;
	game->player->dir.y = sinf(game->player->angle) * 0.1f;
	return SUCC;
}

int game_init(t_game *game, t_file *file)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game->mlx)
		return FAIL;
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return FAIL;
	game->we = mlx_load_png(file->we_path);
	if (!game->we)
		return FAIL;
	game->no = mlx_load_png(file->no_path);
	if (!game->no)
		return FAIL;
	game->ea = mlx_load_png(file->ea_path);
	if (!game->ea)
		return FAIL;
	game->so = mlx_load_png(file->so_path);
	if (!game->so)
		return FAIL;
	game->ceil_color = get_color(file->ce_rgb[0], file->ce_rgb[1], file->ce_rgb[2], 0xFF);
	game->floor_color = get_color(file->fl_rgb[0], file->fl_rgb[1], file->fl_rgb[2], 0xFF);
	game->map = file->parse_map;
	game->mapX = file->map_width;
	game->mapY = file->map_height;
	player_init(game, file);
	return SUCC;
}
