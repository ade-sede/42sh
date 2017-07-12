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
		{
			if (str[i + 1] == 0)
				return (-1);
			return (i);
		}
		i++;
	}
	return (-1);
}

void		parameter_expansion(t_env *env, t_token *token)
{
	char	**split;
	char	*param;
	int		offset;
	char	*result;
	size_t	i;

	i = 0;
	if ((offset = valid_param_expansion(token->value)) != -1)
	{
		result = ft_strnew(0);
		split = ft_strsplit_keep(token->value, WHITESPACES);
		while (split[i])
		{
			param = NULL;
#ifdef EXPAND_DEBUG
			printf("Split[i] == "MAG"#"CYN"%s"MAG"#\n"RESET, split[i]);
#endif
			if ((offset = valid_param_expansion(split[i])) != -1)
			{
#ifdef EXPAND_DEBUG
				printf("Param is valid for expansion\n");
#endif
				param = env_getenv((const char **)env->environ, split[i] + offset + 1, NULL);
				if (param)
					split[i] = ft_strchange(split[i], ft_strdup(param));
				else
					split[i] = ft_strchange(split[i], ft_strnew(0));
#ifdef EXPAND_DEBUG
				printf("After expand split[i] == "MAG"#"CYN"%s"MAG"#"RESET"\n", split[i]);
#endif
			}
			result = ft_strchange(result, ft_strjoin(result, split[i]));
			free(split[i]);
#ifdef EXPAND_DEBUG
			printf("->value after join "MAG"#"CYN"%s"MAG"#"RESET"\n", result);
#endif
			i++;
		}
		free(split);
		token->value = ft_strchange(token->value, result);
	}
}

