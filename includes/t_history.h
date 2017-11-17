#ifndef T_HISTORY_H
# define T_HISTORY_H

typedef struct	s_history
{
	t_lst_head	*command_list;
	t_list_d	*first_new_elem;
	t_list_d	*current_node;
	size_t		history_line;
}				t_history;


#endif
