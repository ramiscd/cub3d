#include "cub3d.h"

/*
** Reads the whole file and returns it as a NULL-terminated array of strings,
** one per line, WITHOUT the trailing '\n'.
** TODO:
**  - count_file_lines() to know how much to allocate.
**  - open() the file, read it line by line (get_next_line from libft).
**  - strip the '\n' of each line.
**  - errors: ERR_OPEN_FILE, ERR_EMPTY_FILE, ERR_MALLOC (via parse_error).
*/
char	**read_file_lines(t_scene *scene, const char *path)
{
	(void)scene;
	(void)path;
	return (NULL);
}

/*
** Returns the number of lines of the file, or -1 if it can't be opened.
*/
int	count_file_lines(const char *path)
{
	(void)path;
	return (-1);
}
