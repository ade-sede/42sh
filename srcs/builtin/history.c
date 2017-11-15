#include "history.h"
#include "libft.h"
#include "environ.h"
#include "get_next_line.h"

#include "local.h"
#include "builtin.h"
#include "t_env.h"
#include "shopt.h"
#include "failure.h"
#include "get_opt.h"

static t_option g_option[] = {
	{1, "c", 2, "clear list", "clear the history list"},
	{0, NULL, 0, NULL, NULL}
};

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

	aff = 1;
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

int			file_to_list(t_hist *h, const char *histf, int i)
{
	int			fd;
	char		*line;
	char		*cat;

	cat = NULL;
	histf = (histf) ? histf : histfile();
	if ((fd = open(histf, O_RDWR | O_CREAT, 0644)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{

	printf("%lx line\n", (long int)line);
		if ((!cat && !*line) || (i && --i))
		{
			free(line);
			continue ;
		}
		if (cat)
		{
			cat[ft_strlen(cat) - 1] = '\n';
			cat = ft_strjoin_free(cat, line, 0b11);
		}
		if (!cat)
			cat = line;
		if (charcmp(cat, ft_strlen(cat) - 1, '\\'))
			continue ;
		if (!i)
			++h->last_line_read;
		routine(h, cat, -1);
		cat = NULL;
	}
	close(fd);
	return (1);
}

void	free_node(void *nd)
{
	t_cmd_node *node;

	node = nd;
	free(node->line);
}

int			builtin_history(t_env *env, const char **argv)
{
	t_hist  *h;
	//int     opt_id;
	size_t  argc;

		(void)env;
	//	(void)argv;
	h = singleton_hist();
	//	t_programinfo pi;

	t_programinfo pi = { "history", "Command Line history", g_option, NULL, 0, 0, 1, 0, NULL, 0, 0 };
	(void)pi;
	argc = ft_arraylen(argv);
	if (argc == 1)
	{
		if (h && h->list)
			double_lst_for_n(h->list->last, h->list->node_count, aff_node, -1);
		return (EXIT_SUCCESS);
	}
/*
**	h->current_cmd = ft_node_new(ft_strdup(*(argv + 1)), -1);
**
** history -s
*/

/*
**history_write_to_histfile(h->list->last);
**
**
** history -w
*/

/*
**	history_write_to_histfile(h->last_read);
**h->last_read = h->list->last;
**
**history -n
*/

/*
**	ft_remove_head(&(h->list), free_node);
**	history -c
*/

	/*
int i;
t_list_d *sup;
i = ft_atoi(*(argv + 1));
if (i > h->list->node_count)
	ft_putendl_fd("out of range", 2);
else
{
	sup = ft_double_lst_get_n((i < 0) ? h->list->first : h->list->last, ~i + 1);
	ft_double_lst_del_one(&(h->list), sup, free_node);
}
**
** history -d offset
*/

/*
**if (*(argv + 1))
**file_to_list(h, *(argv + 2), -1);
**
** history -r filename
*/

/*
**if (*(argv + 1))
**file_to_list(h, *(argv + 2), h->last_line_read - 1);
**
** history -a filename
*/

	/*
	opt_init(&pi, argc, argv);
	while (pi.argerr == 0 && (opt_id = get_opt(&pi) > 0))
		if (opt_id == 1)
			set_shell_opt(env, pi.min, pi.argopt);
	if (pi.argerr)
		return (EXIT_FAILURE);
	add_pos_param(env, argv, pi.argcur, 1);
	*/
	return (EXIT_SUCCESS);
	//	double_lst_for_n(h->list->last, h->list->node_count, aff_node, -1);
}
