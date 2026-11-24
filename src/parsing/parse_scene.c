#include "cub3d.h"

/*
** Sets every field of the scene to its "not set" value:
**  - tex_paths[i] -> NULL
**  - floor_color / ceiling_color -> -1
**  - map.grid -> NULL, map.width / map.height -> 0
**  - spawn -> x = -1, y = -1, dir = '\0'
**  - lines -> NULL
*/
void	init_scene(t_scene *scene)
{
	(void)scene;
}

/*
** Entry point of the parsing. Never returns on error.
** TODO:
**  1. init_scene()
**  2. check_args()             -> argc == 2 and ".cub" extension
**  3. read_file_lines()        -> scene->lines
**  4. parse_elements()         -> returns the index of the first map line
**  5. parse_map()              -> builds scene->map (padded rectangle)
**  6. validate_map_chars(), find_spawn(), validate_map_closed()
**  7. free scene->lines (no longer needed after parsing)
*/
void	parse_scene(t_scene *scene, int argc, char **argv)
{
	(void)scene;
	(void)argc;
	(void)argv;
}

/*
** Prints "Error\n<msg>\n" (print_error), frees the scene (free_scene)
** and exits with EXIT_FAILURE.
*/
void	parse_error(t_scene *scene, const char *msg)
{
	(void)scene;
	(void)msg;
}
