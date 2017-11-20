#include <stdio.h>
#include "libft.h"
#include "bang.h"

int		main(int ac, char *av[])
{
	const char	*input;
	char		*expanded_input;

	if (ac == 2)
		input = av[1];
	else
		input = "!!";
	if (!(expanded_input = bang_expand(input, NULL)))
		expanded_input = ft_strdup(input);
	dprintf(2, "%s\n", expanded_input);
	return (0);
}
