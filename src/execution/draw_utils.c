#include "cub3d.h"

/*
** Writes `color` at (x, y) of the image buffer:
**   dst = img->addr + (y * img->line_len + x * (img->bpp / 8))
**   *(unsigned int *)dst = color
** Ignore coordinates outside the image.
*/
void	put_pixel(t_img *img, int x, int y, int color)
{
	(void)img;
	(void)x;
	(void)y;
	(void)color;
}

/*
** Reads the color at (x, y) of the image buffer (same offset formula).
*/
int	get_pixel(t_img *img, int x, int y)
{
	(void)img;
	(void)x;
	(void)y;
	return (0);
}
