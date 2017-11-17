#include "local.h"
#include "t_env.h"
#include "environ.h"
#include "libft.h"
#include "shopt.h"



#include <stdio.h>

int		local_add_from_key_value(t_env *env, const char *key, const char *value)
{
	t_local	*local;
	char	*environ_value;

	local = create_local(key, value);
	ft_simple_lst_pushback(&env->local, ft_simple_lst_create(local));
	environ_value = env_getenv((const char**)env->environ, key, NULL);
	if (!environ_value || (environ_value && !ft_strequ(environ_value, value)))
		env_add_change(env, key, value);
	return (1);
}

int		local_add_from_string(t_env *env, const char *string)
{
	char	tmp;
	char	*pos;

	pos = ft_strchr(string, '=');
	if (pos == NULL)
		return (0);
	tmp = *pos;
	*pos = 0;
	local_add_from_key_value(env, string, pos + 1);
	*pos = tmp;
	return (1);
}	

int		local_add_change_from_key_value(t_env *env, const char *key, const char *value)
{
	t_list	*node;
	t_local	*local;

	if ((node = local_get_node(env->local, key)))
	{
		local = node->data;
		if (!ft_strequ(local->value, value))
			local->value = ft_strchange(local->value, ft_strdup(value));
	}
	else
		local_add_from_key_value(env, key, value);
	return (1);
}

int		local_add_change_from_string(t_env *env, const char *string)
{
	size_t	pos;
	t_list	*node;
	char	*little_key;

	pos = ft_strichr(string, '=');
	little_key = ft_strsub(string, 0, pos);
	if ((node = local_get_node(env->local, little_key)))
		local_add_change_from_key_value(env, little_key, string + pos + 1);
	else
		local_add_from_string(env, string);
	free(little_key);
	return (1);
}
