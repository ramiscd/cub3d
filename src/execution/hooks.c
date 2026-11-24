#include "cub3d.h"

/*
** Registers every event handler:
**  mlx_hook(win, EVENT_KEY_PRESS,   MASK_KEY_PRESS,   on_key_press,   game);
**  mlx_hook(win, EVENT_KEY_RELEASE, MASK_KEY_RELEASE, on_key_release, game);
**  mlx_hook(win, EVENT_DESTROY,     MASK_NONE,        on_close,       game);
**  mlx_loop_hook(mlx, game_loop, game);
*/
void	setup_hooks(t_game *game)
{
	(void)game;
}

/*
** KEY_ESC -> exit_game(game, EXIT_SUCCESS).
** W/A/S/D/LEFT/RIGHT -> set the matching flag in game->keys to 1.
*/
int	on_key_press(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	return (0);
}

/*
** W/A/S/D/LEFT/RIGHT -> set the matching flag in game->keys to 0.
*/
int	on_key_release(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	return (0);
}

/*
** Red cross of the window -> exit_game(game, EXIT_SUCCESS).
*/
int	on_close(t_game *game)
{
	(void)game;
	return (0);
}
