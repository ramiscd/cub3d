#ifndef PARSING_H
# define PARSING_H

# include "structs.h"

/* ************************************************************************** */
/*                                 ENTRY POINT                                */
/* ************************************************************************** */

/* parse_scene.c */
void	parse_scene(t_scene *scene, int argc, char **argv);
void	init_scene(t_scene *scene);
void	parse_error(t_scene *scene, const char *msg);

/* ************************************************************************** */
/*                                  FILE I/O                                  */
/* ************************************************************************** */

/* check_args.c */
void	check_args(t_scene *scene, int argc, char **argv);
int		has_extension(const char *path, const char *ext);

/* read_file.c */
char	**read_file_lines(t_scene *scene, const char *path);
int		count_file_lines(const char *path);

/* ************************************************************************** */
/*                                  ELEMENTS                                  */
/* ************************************************************************** */

/* parse_elements.c */
int		parse_elements(t_scene *scene);
t_elem	get_element_type(const char *line);
int		all_elements_set(t_scene *scene);

/* parse_texture.c */
void	parse_texture(t_scene *scene, t_tex_id id, const char *line);

/* parse_color.c */
void	parse_color(t_scene *scene, int *dst, const char *line);
int		parse_color_component(const char *str, int *out);
int		pack_rgb(int r, int g, int b);

/* ************************************************************************** */
/*                                    MAP                                     */
/* ************************************************************************** */

/* parse_map.c */
void	parse_map(t_scene *scene, int start);
void	get_map_size(t_scene *scene, int start);
char	*pad_map_line(t_scene *scene, const char *line);

/* validate_map.c */
void	validate_map_chars(t_scene *scene);
void	find_spawn(t_scene *scene);
void	validate_map_closed(t_scene *scene);
int		is_open_cell(t_map *map, int y, int x);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */

/* parse_utils.c */
int		is_empty_line(const char *line);
char	*skip_spaces(const char *str);
int		is_map_line(const char *line);

/* free_scene.c */
void	free_scene(t_scene *scene);

#endif
