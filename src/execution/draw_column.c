#include "cub3d.h"

/*
** Draws the textured wall slice of column x, from draw_start to draw_end.
**   tex     = game->textures[select_texture(ray)]
**   tex_x   = get_tex_x()
**   step    = tex.height / (double)line_height
**   tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step
**   for each y: tex_y = (int)tex_pos (clamped), tex_pos += step,
**               put_pixel(frame, x, y, get_pixel(tex, tex_x, tex_y))
*/
void	draw_column(t_game *game, t_ray *ray, int x)
{
	(void)game;
	(void)ray;
	(void)x;
}

/*
** Picks the texture from the side that was hit and the ray direction:
**   side == 0: dir.x > 0 ? TEX_EA : TEX_WE
**   side == 1: dir.y > 0 ? TEX_SO : TEX_NO
** (see docs/LOGICA_DO_CUB3D.md, "Escolha da textura")
*/
int	select_texture(t_ray *ray)
{
	(void)ray;
	return (TEX_NO);
}

/*
** tex_x = (int)(wall_x * tex.width), mirrored when needed so the
** texture is not drawn backwards on some faces.
*/
int	get_tex_x(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
	return (0);
}
