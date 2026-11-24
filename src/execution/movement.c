#include "cub3d.h"

/*
** Reads game->keys and moves/rotates the player:
**  W -> forward  ( dir)          S -> backward (-dir)
**  A -> left     ( dir.y, -dir.x) D -> right    (-dir.y,  dir.x)
**  LEFT  -> rotate_player(-ROT_SPEED)
**  RIGHT -> rotate_player( ROT_SPEED)
** Every displacement is multiplied by MOVE_SPEED.
*/
void	update_player(t_game *game)
{
	(void)game;
}

/*
** Moves the player by (dx, dy). Test x and y separately with
** is_walkable() so the player can slide along walls.
*/
void	move_player(t_game *game, double dx, double dy)
{
	(void)game;
	(void)dx;
	(void)dy;
}

/*
** Returns 1 if (x, y) is inside the map and the cell is not a wall
** nor MAP_VOID. Returns 0 otherwise.
*/
int	is_walkable(t_game *game, double x, double y)
{
	(void)game;
	(void)x;
	(void)y;
	return (0);
}
