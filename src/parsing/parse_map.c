#include "cub3d.h"

/*
** Builds scene->map from scene->lines[start..].
** TODO:
**  - get_map_size() to set map.width / map.height.
**  - an empty line inside the map -> ERR_MAP_EMPTY_LINE.
**  - anything that is not a map line after the map -> ERR_MAP_NOT_LAST.
**  - allocate map.grid (height + 1, NULL-terminated).
**  - each row = pad_map_line() so every row has exactly `width` chars.
*/
void	parse_map(t_scene *scene, int start)
{
	(void)scene;
	(void)start;
}

/*
** height = number of map lines (trailing empty lines are not counted).
** width  = length of the longest map line.
*/
void	get_map_size(t_scene *scene, int start)
{
	(void)scene;
	(void)start;
}

/*
** Returns a malloc'ed copy of `line` padded with MAP_VOID up to map.width.
*/
char	*pad_map_line(t_scene *scene, const char *line)
{
	(void)scene;
	(void)line;
	return (NULL);
}
