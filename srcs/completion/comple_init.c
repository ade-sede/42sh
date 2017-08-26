#include "lexer.h"
#include "completion.h"
#include "line_editing.h"

t_comple	*singleton_comple()
{
	static t_comple c;

	return (&c);
}

int	comple_init_winch(t_comple *c)
{
	unsigned int	n;

	n = c->nb_matches;
	c->ws_col = get_ws_col();
	c->ws_row = get_ws_row();
	c->nb_colones = get_ws_col() / (c->max_len + 2);
	if (c->nb_colones == 0)
		return (0);
	c->nb_lines = (n % c->nb_colones == 0) ? n / c->nb_colones : (n / c->nb_colones) + 1;
	return (1);
}

t_list	*ft_last_simple_lst(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_previous_last_simple_lst(t_list *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst && lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}

/*
**	pour determiner completion binaire ou completion fichier :
**	on lance un lexer sur la line avec le current word inclu.
**	deux cas:
**		1.le curseur est sur un espace preceder d un espace.
**		2.le curseur est sur un mot a complete.
**	
**	1. on recupere le dernier token "last"
**	si c'est un TK_WORD -> completion fichier;
**	sinon completion binaire
**	
**	2. si il n y a q un seul mayon -> binaire sinon 
**	on recupere le dernier token "last" l avant dernier token "prev_last" :
**		si last est un '&&' ';' ou un connerie du genre -> completion binaire sur le mot d apres
**		si prev
**	
*/

char	**comple_matching(t_line *line, t_comple *c)
{
	t_lexer		lex;
	t_list		*last;
	t_list		*prev_last;
	t_list		*token_list;
	char		*current_word;
	
	(void)c;
	lex = init_lexer(line->buff);
	token_list = start_lex(&lex);
	//lexer_debug(token_list);
	//printf("\n%s|\n", line->buff);
	//printf("\n%d\n", line->pos);
	last = ft_last_simple_lst(token_list);
	current_word = get_current_word_cursor(line);
	if (line->pos == 0 || (line->pos > 0 && (line->buff[line->pos] == ' ' || line->buff[line->pos] == '\0') && line->buff[line->pos - 1] == ' ')) // cas 1.
	{
		if (!last || (last && ((t_token *)last->data)->id == 0))
		{
//			printf("\ncomple file matches\n");
			free_token_list(token_list);
			return (comple_file_matches(line, c, current_word));
		}
		else
		{
//			printf("\ncomple bin  matches\n");
			free_token_list(token_list);
			return (comple_bin_matches(line, c, current_word));
		}
	}
	else 
	{
		if (!token_list->next) // cas 2.
		{
			free_token_list(token_list);
			return (comple_bin_matches(line, c, current_word));
		}
		prev_last = ft_previous_last_simple_lst(token_list);
		if (((t_token *)prev_last->data)->id == 0)
		{
			free_token_list(token_list);
			return (comple_file_matches(line, c, current_word));
		}
		else	
		{
			free_token_list(token_list);
			return (comple_bin_matches(line, c, current_word));
		}
		
	}
//	printf("\nNULL\n");
	return (NULL);

	//	prev_last = ft_previous_last_simple_lst(token_list);
	//	if (*current_word == '.' || ft_strchr(current_word, '/'))
	//		return (comple_file_matches(line, c, current_word));
	//comple_bin_match
}

int	comple_init(t_line *line, t_comple *c)
{
	ft_bzero(c, sizeof(t_comple));
	c->matches = comple_matching(line, c);
	c->max_len = ft_arraymax_f((char**)c->matches, ft_strlen_color);
	c->nb_matches = ft_arraylen((const char**)c->matches);
	if (comple_init_winch(c) == 0)
		return (0);
	c->pos = -1;
	if (c->nb_matches == 1)
	{
		c->pos = 0;
		comple_exit_matched(line, *c, 0);
		return (0);
	}
	else if (c->nb_matches == 0)
	{
		comple_exit_matched(line, *c, 0);
		return (0);
	}
	return (1);
}
