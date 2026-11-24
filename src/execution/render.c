#include "cub3d.h"

/*
** Draws one complete frame into game->frame.
** TODO:
**  1. draw_background()
**  2. for each column x in [0, WIN_WIDTH):
**       init_ray() -> init_step() -> perform_dda() -> compute_wall()
**       -> draw_column()
*/
void	render_frame(t_game *game)
{
	(void)game;
}

/*
** Upper half of the frame  -> scene.ceiling_color.
** Lower half of the frame  -> scene.floor_color.
*/
void	draw_background(t_game *game)
{
	(void)game;
}
