/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:28:46 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 15:20:28 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static void	run_game(t_game *game, t_file *file)
{
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	mlx_key_hook(game->mlx, key_control, game);
	game_loop(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	unload_textures(game);
	free_file(file);
}

int	main(int argc, char *argv[])
{
	t_file		file;
	t_game		game;
	t_player	player;

	game = (t_game){};
	player = (t_player){};
	if (argc != 2)
		return (err_message("Usage: ./cub3D <map.cub>\n", FAIL));
	if (check_exter(argv[1]) == FAIL)
		return (err_message("map is wrong\n", FAIL));
	ft_bzero(&file, sizeof(t_file));
	if (check_inter(&file, argv[1]) == FAIL)
	{
		free_file(&file);
		return (FAIL);
	}
	if (!game_init(&game, &file, &player))
	{
		clean_game(&game, &file);
		return (FAIL);
	}
	run_game(&game, &file);
	return (SUCC);
}
