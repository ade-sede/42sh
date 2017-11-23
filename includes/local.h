#ifndef LOCAL_H
# define LOCAL_H
#include "list.h"
#include "t_env.h"

typedef struct	s_local
{
	char			*key;
	char			*value;
}				t_local;

typedef struct	s_pos_param
{
	int			key;
	char		*value;
}				t_pos_param;

t_local		*create_local(const char *key, const char *value);
void		free_local(void *local);
int			local_add_from_key_value(t_env *env, const char *key, const char *value);
int			local_add_from_string(t_env *env, const char *string);
int			local_add_change_from_key_value(t_env *env, const char *key, const char *value);
int			local_add_change_from_string(t_env *env, const char *string);
int			local_remove(t_env *env, const char *key);


t_list		*local_get_node(t_list *first, const char *key);
void		free_pos_param(void *value);
t_list		*get_pos_param_node(t_list *first, int key);
char		*local_get_value(t_list *first, const char *key);
int			add_pos_param(t_env *env, const char **argv, size_t index, size_t start);
char		*var_get_value(t_env *env, const char *key);

t_pos_param	*create_pos_param(int key, const char *value);
#endif
