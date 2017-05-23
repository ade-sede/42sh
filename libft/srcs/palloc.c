#include "libft.h"
#include "printf.h"

void	*palloc(size_t size, const char *func_name)
{
	void	*mem;

	mem = malloc(size);
	if (mem == NULL)
	{
		ft_dprintf(2, "Malloc returned NULL. Error occured in %s\n", func_name);
		exit(1);
	}
	return (mem);
}
