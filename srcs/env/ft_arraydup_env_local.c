#include "array.h"
#include "str.h"
#include "alloc.h"
#include "local.h"
#include "env.h"

char	**ft_arraydup_env_local(const char **original, t_list **local)
{
	char	**new_environ;
	size_t	original_size;
	size_t	i;

	i = 0;
	original_size = (original == NULL) ? 0 : ft_arraylen(original);
	new_environ = palloc(sizeof(char*) * (original_size + 1));
	while (i != original_size)
	{
		new_environ[i] = ft_strdup(original[i]);
		add_to_local(local, ft_strdup(original[i]));
		i++;
	}
	new_environ[original_size] = NULL;
	return (new_environ);
}
