#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*memory;

	if ((memory = (void*)malloc(sizeof(unsigned char) * size)) == NULL)
		return (NULL);
	ft_bzero(memory, size);
	return (memory);
}
