#include "env.h"
#include "libft.h"
#include "array.h"

void		env_print_environ(const char **environ)
{
	while (*environ)
	{
		ft_putstr(*environ);
		ft_putstr("\n");
		environ++;
	}
}

char		**env_create_environ(const char **original, size_t *new_size)
{
	char		**new_environ;
	size_t		original_size;

	original_size = (original == NULL) ? 0 : ft_arraylen(original);
	new_environ = ft_arraydup(original);
	if (new_size != NULL)
		*new_size = original_size;
	return (new_environ);
}

PS1=qweqwe
LOL=qweqwe
PATH=qweqewq

size_t	index
 value = env_getenv(env->environ, "PATH", NULL);
 value = /bin
 index == 2;

char		*env_getenv(const char **environ, const char *key_start, \
		size_t *index)
{
	size_t		i;
	size_t		key_size;
	char		*value;
	char		*key;

	key = ft_strjoin(key_start, "=");
	key_size = ft_strlen((const char*)key);
	i = 0;
	while (environ[i] && ft_strncmp((const char*)key, environ[i], \
				key_size) != 0)
		i++;
	if (index != NULL)
		*index = i;
	if (environ[i])
		value = (char*)(environ[i] + ft_strichr((char*)environ[i], '=') + 1);
	else
		value = NULL;
	free(key);
	return (value);
}
