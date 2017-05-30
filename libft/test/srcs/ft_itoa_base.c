#include <stdlib.h>
#include "libft.h"

static	int	get_nb_digit(intmax_t value, int base)
{
	int		nb_digit;

	value *= (value > 0) ? -1 : 1;
	nb_digit = 0;
	while (value < 0)
	{
		value /= base;
		nb_digit++;
	}
	return (nb_digit);
}

char		*ft_itoa_base(intmax_t value, int base)
{
	int		nb_digit;
	int		neg;
	char	*str;

	if (value == 0)
		return (ft_strdup("0"));
	nb_digit = get_nb_digit(value, base);
	neg = (base == 10 && value < 0) ? 1 : 0;
	value *= (value > 0) ? -1 : 1;
	if ((str = (char *)malloc((sizeof(char) * nb_digit) + neg + 1)) == NULL)
		return (NULL);
	ft_bzero(str, nb_digit + neg + 1);
	str[0] = '-';
	nb_digit -= 1 - neg;
	while (nb_digit-- >= neg)
	{
		str[nb_digit + 1] = -(value % base)
			+ ((-(value % base) > 9) ? 'a' - 10 : '0');
		value /= base;
	}
	return (str);
}
