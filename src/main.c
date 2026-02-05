/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:28:46 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 15:19:24 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

#if 0
int main(int argc, char *argv[])
{
	t_file	file;

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
	free_file(&file);
	return (SUCC);
}
#else

int main(void)
{
	t_game game = {0};

	mlx_texture_t *we = mlx_load_png("./textures/WE.png");
	if (game_init(&game))
		return FAIL;
	mlx_image_to_window(game.mlx, game.image, 0, 0);
	mlx_key_hook(game.mlx, key_control, &game);
	game_loop(&game);
	mlx_loop(game.mlx);
	mlx_delete_texture(we);
	mlx_terminate(game.mlx);
	free(game.player);
	return SUCC;
}
#endif
