#include "cub3d.h"

/*
** `line` is the full line, e.g. "F 220,100,0".
** TODO:
**  - if *dst != -1 -> ERR_DUPLICATE_ID.
**  - skip the identifier and the spaces after it.
**  - exactly 3 components separated by exactly 2 commas -> ERR_COLOR_FORMAT.
**  - each component via parse_color_component().
**  - *dst = pack_rgb(r, g, b).
*/
void	parse_color(t_scene *scene, int *dst, const char *line)
{
	(void)scene;
	(void)dst;
	(void)line;
}

/*
** Parses a single component ("220"). Only digits are accepted (decide how
** to handle surrounding spaces). Value must be in [0, 255].
** Returns SUCCESS and writes to *out, or FAILURE.
*/
int	parse_color_component(const char *str, int *out)
{
	(void)str;
	(void)out;
	return (FAILURE);
}

/*
** Packs the components into a single int: 0xRRGGBB.
*/
int	pack_rgb(int r, int g, int b)
{
	(void)r;
	(void)g;
	(void)b;
	return (0);
}
