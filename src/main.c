#include "cub3d.h"

/*
** Program flow:
**  1. Parsing   -> fills game.scene (see docs/DIVISAO_DE_TRABALHO.md).
**  2. Execution -> MiniLibX setup, textures, player, hooks.
**  3. mlx_loop  -> runs game_loop() every frame until the window is closed.
*/
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	parse_scene(&game.scene, argc, argv);
	init_game(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (exit_game(&game, EXIT_SUCCESS));
}
