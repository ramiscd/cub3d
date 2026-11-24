#include "cub3d.h"

/*
** Prepares the ray for screen column x:
**   camera_x   = 2 * x / (double)WIN_WIDTH - 1        (-1 left, +1 right)
**   dir        = player.dir + player.plane * camera_x
**   map_x/y    = (int)player.pos.x / (int)player.pos.y
**   delta_dist = |1 / dir.x|, |1 / dir.y|  (use a huge value if dir is 0)
*/
void	init_ray(t_game *game, t_ray *ray, int x)
{
	(void)game;
	(void)ray;
	(void)x;
}

/*
** Sets step_x/step_y (-1 or +1) and the initial side_dist:
**   dir.x < 0: step_x = -1, side_dist.x = (pos.x - map_x) * delta_dist.x
**   dir.x >= 0: step_x = 1, side_dist.x = (map_x + 1.0 - pos.x) * delta_dist.x
**   (same for y)
*/
void	init_step(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
}
