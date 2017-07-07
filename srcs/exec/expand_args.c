#include "libft.h"
#include "env.h"
#include "exec.h"
#include <stdio.h>

static int	valid_param_expansion(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '(' && str[i + 1] != '{')
			return (i);
		i++;
	}
	return (-1);
}

/*
** Not working with quoted strings because it returns after finding the first expand, and doesnt even give it the correct SHELL VARIABLE. Need to isolate all params, and expand them
*/
void		parameter_expansion(t_env *env, t_token *token)
{
	char	**split;
	char	*param;
	int		offset;
	size_t	i;

	i = 0;
	if ((offset = valid_param_expansion(token->value)) != -1)
	{
		split = ft_strsplit_keep(token->value, WHITESPACES);
		while (split[i])
		{
			if ((offset = valid_param_expansion(token->value)) != -1)
			{
				param = env_getenv((const char **)env->environ, split[i] + offset + 1, NULL);
				split[i] = ft_strchange(split[i], param);
			}
			token->value = ft_strchange(token->value, ft_strnew(0));
			token->value = ft_strchange(token->value, ft_strjoin(token->value, split[i]));
			i++;
		}
	}
}
