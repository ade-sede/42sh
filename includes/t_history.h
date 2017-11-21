#ifndef T_HISTORY_H
# define T_HISTORY_H

# include "libft.h"
# define HISTFILE "42sh_history"

/*
 *	Au moment ou on lance un line editing new_node est cree.
 *	Current node est l'addresse de de new.
 *	Quand on effectue des saisie ou qu'on bouge le curseur, le cmd_node concercne est celui qui est la donne de current_node.
 *	Current est soit l'addresse d'un des maillons de la liste, soit l'address de new_node.
 *
 *	Si current != new_node, on copie les infos de current dans new_node.
 *	else if current == new_node ; do nothing.
 *
 *	Suite au lexer/parser new_node->line est remplace par lex->line
 *	Dans l'execution, si besoin est, on peut changer la valeur de new_node.
 *	L'execution est termine, on ajoute new_node a command_list.
 *	Dans la fonction d'ajout a la liste, si histappend est active, on ecrit aussi dans le fichier.
 */

typedef struct	s_history
{
	t_lst_head	*command_list;
	t_list_d	*first_new_elem;
	t_list_d	*current_node;
	size_t		history_line;
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

void			push_in_hist_list_null(t_history *hist);
void			set_hist_node(t_history *hist, char *line, int index);
void			set_new_hist_cmd(t_history *hist, char *str);
t_hist_node		*new_node(void);
char			*histfile(void);
void			init_history(t_history *hist);
void			history_init_line(t_history *hist);
t_history		*singleton_history(void);
void			history_write_to_histfile(t_history *hist, t_list_d *last);
int				history_load(t_history *hist);


#include "environ.h"
int				builtin_history(t_env *env, const char **argv);

#endif
