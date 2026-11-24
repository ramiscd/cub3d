#include "cub3d.h"

/*
** `line` is the full line, e.g. "NO   ./textures/north.xpm".
** TODO:
**  - if scene->tex_paths[id] is already set -> ERR_DUPLICATE_ID.
**  - skip the identifier and the spaces after it.
**  - the path must be a single token (nothing after it except spaces).
**  - must end with ".xpm"                    -> ERR_TEXTURE_EXT.
**  - must be openable with open()            -> ERR_TEXTURE_PATH.
**  - store a malloc'ed copy in scene->tex_paths[id].
*/
void	parse_texture(t_scene *scene, t_tex_id id, const char *line)
{
	(void)scene;
	(void)id;
	(void)line;
}
