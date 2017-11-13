#include "history.h"

void	aff_node(t_list_d *list, int aff)
{
	t_env	*env;

	env = singleton_env();
	ft_putnbr(aff);
	ft_putchar('\t');
	if (env_getenv((const char **)env->environ, "HISTTIMEFORMAT", NULL))
		ft_putstr(((t_cmd_node *)list->data)->timestamp);
	ft_putendl(((t_cmd_node *)list->data)->line);
}

static void    double_lst_for_n(t_list_d *start, int count,\
		void (*f)(t_list_d*, int), int order)
{
	int aff;
	
	aff = 0;
	while (start && count)
	{
		(*f)(start, aff);
		if (order == 1)
			start = start->next;
		if (order == -1)
			start = start->prev;
		count--;
		++aff;
	}
}

int			builtin_history(t_env *env, const char **argv)
{
	t_hist  *h;

	(void)env;
	(void)argv;
	h = singleton_hist();

	double_lst_for_n(h->list->last, h->list->node_count, aff_node, -1);
	return(EXIT_SUCCESS);
}
