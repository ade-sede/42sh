#include "pipe.h"
#include "libft.h"

t_pipe	*create_pipe(int *p)
{
	t_pipe	*new;

	if (!p)
		return (NULL);
	new = ft_memalloc(sizeof(*new));
	new->p = p;
	return (new);
}

void	free_pipe(void *pipe)
{
	t_pipe *a;

	a = (t_pipe*)pipe;
	if (a)
	{
		free(a->p);
		free(a);
	}
}
