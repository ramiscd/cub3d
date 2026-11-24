#include "cub3d.h"

/*
** Clean shutdown, used by ESC, the red cross and the end of main:
**  1. destroy_images()
**  2. mlx_destroy_window()
**  3. mlx_destroy_display() + free(mlx)   (Linux only)
**  4. free_scene()
**  5. exit(status)
** Every pointer may be NULL (partial initialization): check before freeing.
*/
int	exit_game(t_game *game, int status)
{
	(void)game;
	return (status);
}

/*
** print_error(msg) then exit_game(game, EXIT_FAILURE).
*/
void	exit_error(t_game *game, const char *msg)
{
	(void)game;
	(void)msg;
}

/*
** mlx_destroy_image() on game->frame and on each game->textures[i].
*/
void	destroy_images(t_game *game)
{
	(void)game;
}
