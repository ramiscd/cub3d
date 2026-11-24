#include "cub3d.h"

/*
** Called once, right after parse_scene().
** TODO (in this order):
**  1. init_window()   -> mlx_init + mlx_new_window
**  2. init_frame()    -> off-screen image the size of the window
**  3. load_textures() -> the 4 wall textures from scene.tex_paths
**  4. init_player()   -> position / direction / camera plane from scene.spawn
** On failure: exit_error() with the matching ERR_MLX_* message.
*/
void	init_game(t_game *game)
{
	(void)game;
}

/*
** game->mlx = mlx_init();
** game->win = mlx_new_window(..., WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
*/
void	init_window(t_game *game)
{
	(void)game;
}

/*
** game->frame.ptr = mlx_new_image(..., WIN_WIDTH, WIN_HEIGHT);
** game->frame.addr = mlx_get_data_addr(...);
** Every frame is drawn here and then pushed with mlx_put_image_to_window.
*/
void	init_frame(t_game *game)
{
	(void)game;
}
