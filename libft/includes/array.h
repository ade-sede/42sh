#ifndef ARRAY_H
# define ARRAY_H
# include <string.h>

size_t		ft_arraylen(const char **str);
/*
** In file arraydup.c
*/

char		**ft_arraydup(const char **original);

void		ft_arraydel(char ***tabo);
const char	**ft_arraychr(const char **array, const char *str);
size_t		ft_arraymax_f(char **str, size_t (*f)(char *));
#endif
