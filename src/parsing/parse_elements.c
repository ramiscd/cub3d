#include "cub3d.h"

/*
** Walks scene->lines until the first map line.
** For each line, calls get_element_type() and dispatches:
**  - ELEM_NO/SO/WE/EA     -> parse_texture()
**  - ELEM_FLOOR/CEILING   -> parse_color()
**  - ELEM_EMPTY           -> skip
**  - ELEM_MAP             -> stop (check all_elements_set() first)
**  - ELEM_INVALID         -> parse_error(ERR_UNKNOWN_ID)
** Returns the index of the first map line.
** If there is no map line: parse_error(ERR_NO_MAP).
*/
int	parse_elements(t_scene *scene)
{
	(void)scene;
	return (0);
}

/*
** Classifies a line by its identifier, ignoring leading spaces.
** "NO " -> ELEM_NO, "SO " -> ELEM_SO, "WE " -> ELEM_WE, "EA " -> ELEM_EA,
** "F " -> ELEM_FLOOR, "C " -> ELEM_CEILING, "" -> ELEM_EMPTY,
** is_map_line() -> ELEM_MAP, anything else -> ELEM_INVALID.
*/
t_elem	get_element_type(const char *line)
{
	(void)line;
	return (ELEM_INVALID);
}

/*
** Returns 1 if the 4 textures and the 2 colors were set, 0 otherwise.
*/
int	all_elements_set(t_scene *scene)
{
	(void)scene;
	return (0);
}
