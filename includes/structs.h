#ifndef STRUCTS_H
# define STRUCTS_H

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

/*
** Index of each wall texture. Used both for the texture paths (parsing)
** and for the loaded images (execution).
*/
typedef enum e_tex_id
{
	TEX_NO,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	TEX_COUNT
}	t_tex_id;

/*
** Kind of a line found in the .cub file, before the map starts.
*/
typedef enum e_elem
{
	ELEM_NO,
	ELEM_SO,
	ELEM_WE,
	ELEM_EA,
	ELEM_FLOOR,
	ELEM_CEILING,
	ELEM_EMPTY,
	ELEM_MAP,
	ELEM_INVALID
}	t_elem;

/* ************************************************************************** */
/*                     SCENE: OUTPUT OF PARSING (CONTRACT)                    */
/* ************************************************************************** */

/*
** grid:   rectangular map, every row has exactly `width` chars.
**         Short rows are padded with MAP_VOID (' ').
**         The spawn char is replaced by MAP_EMPTY ('0').
** width:  number of columns (x axis).
** height: number of rows (y axis).
*/
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/*
** Player start position in grid coordinates and its orientation.
** dir is one of 'N', 'S', 'E', 'W'.
*/
typedef struct s_spawn
{
	int		x;
	int		y;
	char	dir;
}	t_spawn;

/*
** Everything the parsing produces. Execution only reads from it.
** tex_paths:     indexed by t_tex_id. NULL means "not set yet".
** floor_color:   packed 0xRRGGBB. -1 means "not set yet".
** ceiling_color: packed 0xRRGGBB. -1 means "not set yet".
** lines:         raw file content, one string per line (freed after parsing).
*/
typedef struct s_scene
{
	char	*tex_paths[TEX_COUNT];
	int		floor_color;
	int		ceiling_color;
	t_map	map;
	t_spawn	spawn;
	char	**lines;
}	t_scene;

/* ************************************************************************** */
/*                                 EXECUTION                                  */
/* ************************************************************************** */

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

/*
** Wrapper around a MiniLibX image.
** addr/bpp/line_len/endian come from mlx_get_data_addr().
*/
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

/*
** pos:   position in the map (double, the center of a cell is +0.5).
** dir:   direction vector (where the player is looking).
** plane: camera plane, perpendicular to dir (defines the FOV).
*/
typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

/*
** State of a single ray (one per screen column).
** side: 0 if an x-side (vertical grid line) was hit, 1 if a y-side.
*/
typedef struct s_ray
{
	double	camera_x;
	t_vec	dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_id;
	double	wall_x;
}	t_ray;

/*
** 1 while the key is held down, 0 otherwise.
*/
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

/* ************************************************************************** */
/*                                MAIN STRUCT                                 */
/* ************************************************************************** */

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		textures[TEX_COUNT];
	t_scene		scene;
	t_player	player;
	t_keys		keys;
}	t_game;

#endif
