#include "cub3d.h"

/*
** Calls load_texture() for each id in [0, TEX_COUNT), using
** game->scene.tex_paths[id] -> game->textures[id].
*/
void	load_textures(t_game *game)
{
	(void)game;
}

/*
** img->ptr  = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
** img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, ...);
** If ptr is NULL -> exit_error(ERR_TEXTURE_LOAD).
*/
void	load_texture(t_game *game, t_img *img, char *path)
{
	(void)game;
	(void)img;
	(void)path;
}
