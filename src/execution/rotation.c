#include "cub3d.h"

/*
** Rotates dir AND plane by `angle` radians (rotation matrix):
**   x' = x * cos(a) - y * sin(a)
**   y' = x * sin(a) + y * cos(a)
** Save the old x before overwriting it.
** With the y axis pointing down, a positive angle turns to the right.
*/
void	rotate_player(t_player *player, double angle)
{
	(void)player;
	(void)angle;
}
