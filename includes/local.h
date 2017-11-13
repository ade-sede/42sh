#ifndef LOCAL_H
# define LOCAL_H
#include "list.h"

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

t_local	*create_local(const char *key, const char *value);
void				free_local(void *local);
int		local_add_from_key_value(t_list **first, const char *key, const char *value);
int		local_add_from_string(t_list **first, const char *string);
int		local_add_change_from_key_value(t_list **first, const char *key, const char *value);
int		local_add_change_from_string(t_list **first, const char *string);
int		local_remove(t_list **local_list, const char *key);


t_list		*local_get_node(t_list *first, const char *key);
void		free_pos_param(void *value);
t_list		*get_pos_param_node(t_list *first, int key);
char			*local_get_value(t_list *first, const char *key);
#endif
