#include "cub3d.h"

/*
** TODO:
**  - argc must be exactly 2, otherwise parse_error(ERR_USAGE).
**  - argv[1] must end with ".cub", otherwise parse_error(ERR_EXTENSION).
**    Watch out for edge cases: ".cub", "map.cub.txt", "map.cu", "dir/.cub".
*/
void	check_args(t_scene *scene, int argc, char **argv)
{
	(void)scene;
	(void)argc;
	(void)argv;
}

/*
** Returns 1 if `path` ends with `ext` and has at least one char before it
** (ignoring the directory part), 0 otherwise.
*/
int	has_extension(const char *path, const char *ext)
{
	(void)path;
	(void)ext;
	return (0);
}
