
// #include "../include/cube3D.h"

// void    start_to_display(t_game *game, t_file *files)
// {
//     mlx_set_setting(MLX_STRETCH_IMAGE, 1);
//     game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
//     game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
//     //transfer from files to game
// 	load_textures(game, &files);
//     mlx_image_to_window(game->mlx, game->img, 0, 0);
//     mlx_loop(game->mlx);
// }

// void load_textures(t_game *game, t_file *files)
// {
//     game->tex.no = mlx_load_png(files->no);
//     game->tex.so = mlx_load_png(files->so);
//     game->tex.we = mlx_load_png(files->we);
//     game->tex.ea = mlx_load_png(files->ea);
//     if (!game->tex.no || !game->tex.so || !game->tex.we
//     || !game->tex.ea)
//         err_message("Failed to load texture", FAIL);
// }