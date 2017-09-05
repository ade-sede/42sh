#include "libft.h"
#include <stdio.h>

int	main()
{
	char **tab;
	char	*tmp_addr;

	tab = malloc(4 * sizeof(char *));
	tab[0] = ft_strdup("lala");
	tab[1] = ft_strdup("lolo");
	tmp_addr = tab[1];
	printf("%s\n", tmp_addr);
	tab[2] = ft_strdup("lulu");
	tab[3] = NULL;
	//free(tab[1]);
	ft_arraydel(&tab);
	printf("%p\n", tab);
	//printf("%s\n", tmp_addr);
	//printf("%p\n", tmp_addr);
	return (0);
}
