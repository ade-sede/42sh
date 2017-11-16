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
	{1, "c", OPTION_BOOL, "\t", "clear the history list"},
	{2, "d", OPTION_STRING, "offset", "delete one node"},
	{3, "a", OPTION_BOOL, "[filename]", "Append the new history lines"},
	{4, "n", OPTION_BOOL, "[filename]", "Append the history lines not already read from the history file"},
	{5, "r", OPTION_BOOL, "[filename]", "append the current history file"},
	{6, "w", OPTION_BOOL, "[filename]", "Write out the current history to the history file"},
	{7, "s", OPTION_STRING, "args", "The args are added to the end of the history list as a single entry."},
	{0, NULL, 0, NULL, NULL}
};

/*
static t_programinfo pi = {
	"history", "Command Line history", 
	g_option, NULL, 0, 0, 1, 0, NULL, 0, 0
};
*/

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

char	*joinarg(const char **arg)
{
	int		i;
	char	*ret;

	i = 2;
	ret = ft_strdup(*(arg + i));
	while (*(arg + ++i))
		ret = ft_strjoin3_free(ret, " ", (char *)*(arg + i), 1);
	return (ret);
}

void opt(int opt_id, t_hist *h, const char **argv)
{
	int i;
	t_list_d *sup;
	
	if (opt_id == 1)
	{
		ft_remove_head(&(h->list), free_node);
		h->last_read = NULL;
	}
	else if (opt_id == 2)
	{
		i = ft_atoi(*(argv + 2));
		if (i > h->list->node_count)
			ft_putendl_fd("out of range", 2);
		else
		{
			sup = ft_double_lst_get_n((i < 0) ? h->list->first : h->list->last, ~i + 1);
			ft_double_lst_del_one(&(h->list), sup, free_node);
		}
	}
	else if (opt_id == 3)
		file_to_list(h, *(argv + 2), h->last_line_read - 1);
	else if (opt_id == 5)
		file_to_list(h, *(argv + 2), 0);
	else if (opt_id == 4)
	{
		history_write_to_histfile(h->last_read, *(argv + 2));
		h->last_read = h->list->first;
	}
	else if (opt_id == 6)
	{
		history_write_to_histfile(h->list->last, *(argv + 2));
	}
	else if (opt_id == 7)
		h->current_cmd = ft_node_new(joinarg(argv), -1); //a changer
}

int aff_hist(int argc, const char **argv, t_hist *h)
{
	int i;
	if (argc == 1)
		i = h->list->node_count;
	else if (argc == 2)
		i = ft_atoi(*(argv + 1));
	else
		return (EXIT_FAILURE);
	if (h && h->list)
		double_lst_for_n(h->list->last, h->list->node_count, aff_node, -1);
	return (EXIT_SUCCESS);
}

int			builtin_history(t_env *env, const char **argv)
{
	t_hist  *h;
	int     opt_id;
	size_t  argc;

		(void)env;
	//	(void)argv;
	h = singleton_hist();
	//	t_programinfo pi;
	t_programinfo pi = { "history", "Command Line history", g_option, NULL, 0, 0, 1, 0, NULL, 0, 0 };

	argc = ft_arraylen(argv);
	opt_init(&pi, argc, argv);
	opt_id = get_opt(&pi);
	if (pi.argerr)
	{
		get_opt_display_error(&pi, opt_id);
		return (EXIT_FAILURE);
	}
	if (opt_id < 1)
		return(aff_hist(argc, argv, h));
	opt(opt_id, h, argv);
	return (EXIT_SUCCESS);
}
