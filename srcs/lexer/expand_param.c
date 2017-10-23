/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/23 15:47:43 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "exec.h"
#include "local.h"

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

/*static t_list	*find_value(t_list *local, char *new_data)
{
	char	*new_key;
	char	*key;

	new_key = new_data;
	while (local)
	{
		key = key_of_local(local->data, '=');
		if (ft_strcmp(new_key, key) == 0)
		{
			free(new_key);
			free(key);
			return (local);
		}
		free(key);
		local = local->next;
	}
	free(new_key);
	return (NULL);
}*/

static char	*expand_from_env(t_env *env, char *key, int offset)
{
	char	*param;
	//t_list	*local_elem;
	char	*ret;
	//size_t	eq_pos;

	//param = env_getenv((const char **)env->environ, key + offset + 1, NULL);
	
	//local_elem = find_value(env->local, key + offset + 1);
	//eq_pos = ft_strichr(local_elem->data, '=');
	//param = local_elem->data + eq_pos + 1;
	param = local_get_var(env->local, key + offset + 1);
	if (param)
		ret = ft_strdup(param);
	else
		ret = ft_strnew(0);
	return (ret);
}



void		parameter_expansion(t_env *env, t_token *token)
{
	char	**split;
	int		offset;
	char	*result;
	size_t	i;

	i = 0;
	if ((offset = valid_param_expansion(token->value)) != -1)
	{
		result = ft_strnew(0);
		split = ft_strsplit_keep(token->value, WHITESPACES"/");
		while (split[i])
		{
			if ((offset = valid_param_expansion(split[i])) != -1)
				split[i] = ft_strchange(split[i], \
						expand_from_env(env, split[i], offset));
			result = ft_strchange(result, ft_strjoin(result, split[i]));
			free(split[i]);
			i++;
		}
		free(split);
		token->value = ft_strchange(token->value, result);
	}
}
