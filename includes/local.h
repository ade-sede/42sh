#ifndef LOCAL_H
# define LOCAL_H

typedef struct	s_local_list
{
	struct s_local_list	*next;
	char			*key;
	char			*value;
}				t_local_list;

t_local_list	*create_local(const char *key, const char *value);
int		local_add_from_key_value(t_local_list **first, const char *key, const char *value);
int		local_add_from_string(t_local_list **first, const char *string);
int	local_add_change_from_key_value(t_local_list **first, const char *key, const char *value);
#endif
