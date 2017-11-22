#ifndef T_HISTORY_H
# define T_HISTORY_H

# include "libft.h"
# include "t_env.h"


typedef struct	s_histfile
{
	const char	*filename;
	size_t		ln;
	t_list_d	*last_cmd;
}				t_histfile;

typedef struct	s_history {
	t_lst_head	*command_list;
	t_list_d	*current;
	t_list_d	*new_command;
	t_list		*histfile_list;
}				t_history;

typedef struct	s_hist_cmd_node
{
	t_word			line;
	int				index;
	struct timeval	timestamp;
	int				modified;
}				t_hist_cmd_node;

typedef struct	s_hist_node
{
	t_hist_cmd_node history;
	t_hist_cmd_node hist_modif;
}				t_hist_node;

/*
**	t_history.c
*/

t_history	*singleton_history(void);
void		init_history(t_env *env, t_history *hist);

/*
t_hist_node *create_hist_node(void);
*/

void	update_timestamp(t_hist_cmd_node *node);
void	update_line_hist_cmd_node(t_hist_cmd_node *node, const char *line);
void	append_line_hist_cmd_node(t_hist_cmd_node *node, const char *cat);
void	append_char_hist_cmd_node(t_hist_cmd_node *node, const char c);
void	index_hist_cmd_node(t_hist_cmd_node *node, size_t index);
void	destroy_hist_cmd_node(t_hist_cmd_node *node);


t_hist_node *create_hist_node(void);
t_hist_cmd_node *get_cmd_node(t_hist_node *histnode);
void	destroy_hist_cmd_node(t_hist_cmd_node *node);
void	copy_cmd_node(t_hist_cmd_node *source, t_hist_cmd_node *dest);
void	restore_cmd_node(t_list_d *ptr);
void	destroy_hist_node(t_list_d *l);


t_histfile	*create_histfile(const char *filename);
t_histfile	*get_histfile(t_list *histfile, const char *filename);
t_histfile	*add_histfile(t_list **histfile_l, const char *filename);
#endif


/* init_history; */
/* while (1) */
/* { */
/* copy(s:hist d:mod) */
/* construct_cache: */
/* { */
/* 	cache = new history; */
/* 	current = cache; */
/* } */
/* line_editing: */
/* { */
/* 	fill_current: */
/* } */
/* destroy_cache: */
/* { */
/* 	free(cache) */
/* } */
/* lex->line - ret_line_editing(); */
/* while lex-parse: */
/* { */
/* 	construct_cache: */
/* 	opt:line_editing: */
/* 	{ */
/* //		construct_cache: */
/* 		fill_current: */
/* 	} */
/* 		lex-line += current->line; */
/* 	destroy_cache: */
/* 	//append(s:retour_reopen d:new_command) */
/* } */
/* new_command = ft_lstnew(); */
/* subs(s:lex->line, d:new_command:history); new_command:history:modified = 1 */
/* exec (hist->cache) */
/* new_command */
/* add_to_list; && if (histappend) write to file */

/* } */
