#ifndef LOCAL_H
# define LOCAL_H

typedef struct	s_local_list
{
	struct s_local_list	*next
	char			*key;
	char			*value;
	char			*key_value;
}				t_local_list;

#endif
