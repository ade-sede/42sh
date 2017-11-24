#include "libft.h"

void	ft_arraydel(char ***tab)
{
	char	**tmp;

	tmp = *tab;
	while (tmp && *tmp)
	{
		ft_strdel(tmp);
		tmp++;
	}
	free(*tab);
	*tab = NULL;
}
