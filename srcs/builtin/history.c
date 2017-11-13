#include "history.h"
#include "libft.h"

void	aff_node(t_list_d *list, int aff)
{
	t_env	*env;
	char	*format;
	char	result[100];

	env = singleton_env();
	ft_putnbr(aff);
	ft_putchar('\t');
	if ((format = env_getenv((const char **)env->environ, "HISTTIMEFORMAT", 0)))
	{
		strftime(result, sizeof(result), format,
				localtime(&((t_cmd_node *)list->data)->timestamp.tv_sec));
		ft_putstr(result);
	//ft_putnbr((ssize_t)((t_cmd_node *)list->data)->timestamp.tv_sec);
	//	ft_putstr(((t_cmd_node *)list->data)->timestamp);
	}
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
	t_programinfo pi;


	opt_init(&pi, ft_strlen((char *)argv), argv);
	//ft_putnbr(pi.argc);
	//ft_putendl(*(pi.argv));
	get_opt(&pi);
	ft_putendl(*(pi.argv));



	double_lst_for_n(h->list->last, h->list->node_count, aff_node, -1);
	return(EXIT_SUCCESS);
}
