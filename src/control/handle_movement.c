/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:34:40 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 15:20:15 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static bool	is_wall(t_game *game, t_vector pos)
{
	int	map_x;
	int	map_y;

	map_x = (int)pos.x;
	map_y = (int)pos.y;
	if (map_x < 0)
		map_x = 0;
	if (map_y < 0)
		map_y = 0;
	return (game->map[map_y][map_x] == WALL);
}

void	turn(t_game *game, t_turn dir)
{
	t_player	*p;

	p = game->player;
	if (dir == LEFT)
		p->angle -= TURN_ANGLE;
	else
		p->angle += TURN_ANGLE;
	if (p->angle < 0)
		p->angle += 2 * PI;
	p->dir.x = cosf(p->angle);
	p->dir.y = sinf(p->angle);
}

void	move(t_game *game, t_move dir)
{
	t_player	*p;
	t_vector	new_pos;

	p = game->player;
	if (dir == FORWARD)
		new_pos = v2f_add(p->pos, v2f_scale(p->dir, SPEED
					* game->delta_time));
	else
		new_pos = v2f_sub(p->pos, v2f_scale(p->dir, SPEED
					* game->delta_time));
	if (!is_wall(game, new_pos))
		p->pos = new_pos;
}

void	move_left_or_right(t_game *game, t_move dir)
{
	t_vector	new_dir;
	t_vector	new_pos;
	t_player	*p;

	p = game->player;
	if (dir == MOVE_LEFT)
		new_dir = (t_vector){p->dir.y, -p->dir.x};
	else
		new_dir = (t_vector){-p->dir.y, p->dir.x};
	new_pos = v2f_add(p->pos, v2f_scale(new_dir, SPEED
				* game->delta_time));
	if (!is_wall(game, new_pos))
		p->pos = new_pos;
}

void	handle_movement(void *param)
{
	t_game		*game;

	game = param;
	if (game->turn_left)
		turn(game, LEFT);
	if (game->turn_right)
		turn(game, RIGHT);
	if (game->left)
		move_left_or_right(game, MOVE_LEFT);
	if (game->right)
		move_left_or_right(game, MOVE_RIGHT);
	if (game->forward)
		move(game, FORWARD);
	if (game->backward)
		move(game, BACKWARD);
	if (game->mouse_enabled)
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	else
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
}
