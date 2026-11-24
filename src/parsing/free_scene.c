#include "cub3d.h"

/*
** Frees everything the parsing allocated and sets the pointers to NULL:
**  - tex_paths[0..TEX_COUNT-1]
**  - map.grid (free_strs)
**  - lines    (free_strs)
** Must be safe to call on a partially filled scene.
*/
void	free_scene(t_scene *scene)
{
	(void)scene;
}
