#include "libft.h"
#include "env.h"
#include "exec.h"
#include <stdio.h>

static short int	dollar_sign_is_valid(const char *argv, size_t i)
{
	short int	valid;

	valid = false;
	if (charcmp(argv, i, '$'))
		valid = true;
	return (valid);
}

static char	*expand_from_split(t_env env, char **split)
{
	char	*expanded_str;
	char	*tmp;
	char	*value;

	/* expanded_str = malloc(1); */
	/* *expanded_str = 0; */
	expanded_str = ft_strnew(0);
	value = NULL;
	while (split && *split)
	{
		if (ft_strequ((const char*)*split, "$?"))
			value = ft_itoa_base(env.previous_exit, 10);
		else if (**split == '$')
			value = ft_strdup(env_getenv((const char**)env.environ, *split + 1, NULL));
		else
			value = ft_strdup(*split);
		if (value)
		{
			tmp = expanded_str;
			expanded_str = ft_strjoin(expanded_str, value);
			free(value);
			free(tmp);
		}
		free(*split);
		split++;
	}
	/* free(split); */
	/* printf("%s\n", expanded_str); */
	return (expanded_str);
}

void		exec_expand_args(t_env env, char **argv)
{
	size_t j;
	size_t i;
	short int	dollar_sign;
	char	**split;

	dollar_sign = false;
	j = 0;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (!dollar_sign && argv[j][i] == '$')
			{
				dollar_sign = dollar_sign_is_valid((const char*)argv[j], i);
			}
			i++;
		}
		if (dollar_sign)
		{
			split = ft_strsplit_keep((const char*)argv[j], WHITESPACES);
			argv[j] = ft_strchange(argv[j], expand_from_split(env, split));
		}
		j++;
	}
}
