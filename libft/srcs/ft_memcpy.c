#include "libft.h"
#include "printf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s1;

	s1 = dst;
	while (n != 0)
	{
		*s1 = *(unsigned char*)src;
		s1++;
		src++;
		n--;
	}
	return (dst);
}


void	**ft_addrcpy(void **dst, const void **src, size_t n)
{
	void	**s1;

	s1 = dst;
	while (n != 0)
	{
		*s1 = *(void**)src;
		s1++;
		src++;
		n--;
	}
	return (dst);
}
