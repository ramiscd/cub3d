#include "cub3d.h"

/*
** pos = center of the spawn cell: (spawn.x + 0.5, spawn.y + 0.5).
** Then set_player_direction() with spawn.dir.
*/
void	init_player(t_game *game)
{
	(void)game;
}

/*
** Remember: the y axis grows DOWNWARDS (row index of the grid).
**   'N': dir = ( 0, -1)  plane = ( FOV_PLANE,  0)
**   'S': dir = ( 0,  1)  plane = (-FOV_PLANE,  0)
**   'E': dir = ( 1,  0)  plane = ( 0,  FOV_PLANE)
**   'W': dir = (-1,  0)  plane = ( 0, -FOV_PLANE)
*/
void	set_player_direction(t_player *player, char dir)
{
	(void)player;
	(void)dir;
}
