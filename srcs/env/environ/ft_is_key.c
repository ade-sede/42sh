#include "libft.h"

int		is_key(const char *key)
{
	return (ft_str_isdigit(key) || ft_strequ(key, "@") || ft_strequ(key, "*") ||
		ft_strequ(key, "#") || ft_strequ(key, "?") || ft_strequ(key, "-") ||
		ft_strequ(key, "$") || ft_strequ(key, "!"));
}
