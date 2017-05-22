#include "libft.h"

char	*ft_strsurround(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	return (str);
}
