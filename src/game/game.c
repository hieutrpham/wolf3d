/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:47:55 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 13:45:09 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	fps_hook(void *param)
{
	t_game	*game;
	float	current_time;
	float	delta_time;

	game = param;
	current_time = mlx_get_time();
	delta_time = current_time - game->last_time;
	game->last_time = current_time;
	game->delta_time = delta_time;
}

void	mouse_rotation(void *param)
{
	int			x;
	int			y;
	t_game		*game;
	t_player	*p;
	int			delta_x;

	game = param;
	p = game->player;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	delta_x = x - WIDTH / 2;
	p->angle += delta_x * MOUSE_SENSITIVITY;
	if (p->angle < 0)
		p->angle += 2 * PI;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	p->dir.x = cosf(p->angle);
	p->dir.y = sinf(p->angle);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}

void	game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx, fps_hook, game);
	mlx_loop_hook(game->mlx, handle_movement, game);
	mlx_loop_hook(game->mlx, mouse_rotation, game);
	mlx_loop_hook(game->mlx, render_ceiling, game);
	mlx_loop_hook(game->mlx, render_floor, game);
	mlx_loop_hook(game->mlx, draw_rays, game);
}

bool	player_init(t_game *game, t_player *player, t_file *file)
{
	game->player = player;
	if (file->player_dir == 'N')
		game->player->angle = 3 * PI / 2;
	if (file->player_dir == 'E')
		game->player->angle = PI;
	if (file->player_dir == 'W')
		game->player->angle = 2 * PI;
	if (file->player_dir == 'S')
		game->player->angle = PI / 2;
	game->player->pos.x = file->player_x + 0.5f;
	game->player->pos.y = file->player_y + 0.5f;
	game->player->dir.x = cosf(game->player->angle);
	game->player->dir.y = sinf(game->player->angle);
	return (true);
}

bool	game_init(t_game *game, t_file *file, t_player *player)
{
	game->delta_angle = FOV * RAD / WIDTH;
	game->mlx = mlx_init(WIDTH, HEIGHT, "wolf3D", true);
	if (!game->mlx)
		return (false);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return (false);
	if (!load_texture(game, file))
		return (false);
	game->ceil_color = get_color(file->ce_rgb[0], file->ce_rgb[1],
			file->ce_rgb[2], 0xFF);
	game->floor_color = get_color(file->fl_rgb[0], file->fl_rgb[1],
			file->fl_rgb[2], 0xFF);
	game->map = file->parse_map;
	game->map_width = file->map_width;
	game->map_height = file->map_height;
	if (!player_init(game, player, file))
		return (false);
	return (true);
}
