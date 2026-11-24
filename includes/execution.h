#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"

/* ************************************************************************** */
/*                               INITIALIZATION                               */
/* ************************************************************************** */

/* init_game.c */
void	init_game(t_game *game);
void	init_window(t_game *game);
void	init_frame(t_game *game);

/* init_textures.c */
void	load_textures(t_game *game);
void	load_texture(t_game *game, t_img *img, char *path);

/* init_player.c */
void	init_player(t_game *game);
void	set_player_direction(t_player *player, char dir);

/* ************************************************************************** */
/*                              EVENTS / LOOP                                 */
/* ************************************************************************** */

/* hooks.c */
void	setup_hooks(t_game *game);
int		on_key_press(int keycode, t_game *game);
int		on_key_release(int keycode, t_game *game);
int		on_close(t_game *game);

/* game_loop.c */
int		game_loop(t_game *game);

/* ************************************************************************** */
/*                                  MOVEMENT                                  */
/* ************************************************************************** */

/* movement.c */
void	update_player(t_game *game);
void	move_player(t_game *game, double dx, double dy);
int		is_walkable(t_game *game, double x, double y);

/* rotation.c */
void	rotate_player(t_player *player, double angle);

/* ************************************************************************** */
/*                                 RAYCASTING                                 */
/* ************************************************************************** */

/* render.c */
void	render_frame(t_game *game);
void	draw_background(t_game *game);

/* raycast.c */
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_step(t_game *game, t_ray *ray);

/* dda.c */
void	perform_dda(t_game *game, t_ray *ray);
void	compute_wall(t_game *game, t_ray *ray);

/* draw_column.c */
void	draw_column(t_game *game, t_ray *ray, int x);
int		select_texture(t_ray *ray);
int		get_tex_x(t_game *game, t_ray *ray);

/* draw_utils.c */
void	put_pixel(t_img *img, int x, int y, int color);
int		get_pixel(t_img *img, int x, int y);

/* ************************************************************************** */
/*                                  CLEANUP                                   */
/* ************************************************************************** */

/* cleanup.c */
int		exit_game(t_game *game, int status);
void	exit_error(t_game *game, const char *msg);
void	destroy_images(t_game *game);

#endif
