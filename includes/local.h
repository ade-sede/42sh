#ifndef LOCAL_H
# define LOCAL_H

# include "../libft/includes/libft.h"

char	*key_of_local(char *data, int c);
char	*value_of_local(char *data, int c);

char	*local_get_var(t_list *local, char *key_want);
int		add_to_local(t_list **local, char *data);
int		remove_var_from_local(t_list *local, char *key);

#endif
