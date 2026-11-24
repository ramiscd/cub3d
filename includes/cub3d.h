#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"
# include "mlx.h"

# include "defines.h"
# include "structs.h"
# include "parsing.h"
# include "execution.h"

/* ************************************************************************** */
/*                           SHARED UTILS (src/utils)                         */
/* ************************************************************************** */

/* error.c */
void	print_error(const char *msg);

/* free_utils.c */
void	free_strs(char **strs);

#endif
