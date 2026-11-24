#ifndef DEFINES_H
# define DEFINES_H

/* ************************************************************************** */
/*                                  GENERAL                                   */
/* ************************************************************************** */

# define SUCCESS 0
# define FAILURE 1

/* ************************************************************************** */
/*                                   WINDOW                                   */
/* ************************************************************************** */

# define WIN_TITLE "cub3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

/* ************************************************************************** */
/*                                   PLAYER                                   */
/* ************************************************************************** */

/* Length of the camera plane. 0.66 gives a field of view of ~66 degrees. */
# define FOV_PLANE 0.66
/* Movement speed in map cells per frame. */
# define MOVE_SPEED 0.05
/* Rotation speed in radians per frame. */
# define ROT_SPEED 0.04

/* ************************************************************************** */
/*                                MAP SYMBOLS                                 */
/* ************************************************************************** */

# define MAP_EMPTY '0'
# define MAP_WALL '1'
# define MAP_VOID ' '
# define MAP_VALID_CHARS "01NSEW "
# define MAP_SPAWN_CHARS "NSEW"

/* ************************************************************************** */
/*                           KEYCODES (X11 / LINUX)                           */
/* ************************************************************************** */

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* ************************************************************************** */
/*                              X11 EVENTS/MASKS                              */
/* ************************************************************************** */

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_DESTROY 17
# define MASK_KEY_PRESS 1L
# define MASK_KEY_RELEASE 2L
# define MASK_NONE 0L

/* ************************************************************************** */
/*                               ERROR MESSAGES                               */
/* ************************************************************************** */

# define ERR_USAGE "Usage: ./cub3D <map.cub>"
# define ERR_EXTENSION "Map file must have the .cub extension"
# define ERR_OPEN_FILE "Could not open the map file"
# define ERR_EMPTY_FILE "Map file is empty"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_UNKNOWN_ID "Unknown element identifier"
# define ERR_DUPLICATE_ID "Duplicated element identifier"
# define ERR_MISSING_ID "Missing element (NO, SO, WE, EA, F or C)"
# define ERR_TEXTURE_PATH "Invalid texture path"
# define ERR_TEXTURE_EXT "Texture file must have the .xpm extension"
# define ERR_COLOR_FORMAT "Invalid color format (expected R,G,B)"
# define ERR_COLOR_RANGE "Color component out of range [0,255]"
# define ERR_NO_MAP "Map is missing"
# define ERR_MAP_NOT_LAST "Map must be the last element of the file"
# define ERR_MAP_EMPTY_LINE "Map contains an empty line"
# define ERR_MAP_CHAR "Map contains an invalid character"
# define ERR_NO_SPAWN "Map has no player spawn"
# define ERR_MULTI_SPAWN "Map has more than one player spawn"
# define ERR_MAP_OPEN "Map is not closed by walls"
# define ERR_MLX_INIT "Failed to initialize MiniLibX"
# define ERR_MLX_WINDOW "Failed to create the window"
# define ERR_MLX_IMAGE "Failed to create an image"
# define ERR_TEXTURE_LOAD "Failed to load a texture"

#endif
