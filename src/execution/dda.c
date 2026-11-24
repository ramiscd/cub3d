#include "cub3d.h"

/*
** Digital Differential Analysis: jump cell by cell until a wall is hit.
** Loop:
**   if side_dist.x < side_dist.y: advance in x, side = 0
**   else:                         advance in y, side = 1
**   stop when grid[map_y][map_x] == MAP_WALL
*/
void	perform_dda(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
}

/*
** After the hit:
**   perp_dist   = side == 0 ? side_dist.x - delta_dist.x
**                           : side_dist.y - delta_dist.y
**   line_height = (int)(WIN_HEIGHT / perp_dist)
**   draw_start  = -line_height / 2 + WIN_HEIGHT / 2   (clamp to 0)
**   draw_end    =  line_height / 2 + WIN_HEIGHT / 2   (clamp to H - 1)
**   wall_x      = exact hit point on the wall, in [0, 1)
*/
void	compute_wall(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
}
