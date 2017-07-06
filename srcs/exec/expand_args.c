#include "libft.h"
#include "env.h"
#include "exec.h"
#include <stdio.h>

static short int	dollar_sign_is_valid(const char *argv, size_t i)
{
	short int	valid;

	valid = FALSE;
	if (charcmp(argv, i, '$'))
		valid = TRUE;
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

void		exec_expand_args(t_env env, t_token	*token)
{
	size_t i;
	short int	dollar_sign;
	char	**split;

	i = 0;
	dollar_sign = FALSE;
	while (token->value[i])
	{
		i = 0;
		while (token->value[i])
		{
			if (!dollar_sign && token->value[i] == '$')
				dollar_sign = dollar_sign_is_valid((const char*)token->value, i);
			i++;
		}
		if (dollar_sign)
		{
			split = ft_strsplit_keep((const char*)token->value, WHITESPACES);
			token->value = ft_strchange(token->value, expand_from_split(env, split));
		}
	}
}
