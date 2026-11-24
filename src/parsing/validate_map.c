#include "cub3d.h"

/*
** Every char of the grid must be in MAP_VALID_CHARS -> ERR_MAP_CHAR.
*/
void	validate_map_chars(t_scene *scene)
{
	(void)scene;
}

/*
** Finds the single spawn char (N, S, E, W).
** TODO:
**  - none                -> ERR_NO_SPAWN.
**  - more than one       -> ERR_MULTI_SPAWN.
**  - fill scene->spawn (x = column, y = row, dir = the char).
**  - replace the spawn char in the grid with MAP_EMPTY.
*/
void	find_spawn(t_scene *scene)
{
	(void)scene;
}

/*
** For every walkable cell ('0', after the spawn was replaced),
** is_open_cell() must be false, otherwise -> ERR_MAP_OPEN.
*/
void	validate_map_closed(t_scene *scene)
{
	(void)scene;
}

/*
** Returns 1 if the cell (y, x) touches the "outside": it is on the border
** of the grid, or one of its 4 neighbours (up, down, left, right)
** is MAP_VOID. Returns 0 otherwise.
*/
int	is_open_cell(t_map *map, int y, int x)
{
	(void)map;
	(void)y;
	(void)x;
	return (1);
}
