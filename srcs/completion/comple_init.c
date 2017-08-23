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
	c->nb_colones = get_ws_col() / (c->max_len + 2);
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
**		1.le curseur est sur un mot a complete.
**		2.le curseur est sur un espace preceder d un espace.
**	
**	2. on recupere le dernier token "last"
**	si c'est un TK_WORD -> completion fichier;
**	sinon completion binaire
**	
**	1. on recupere le dernier token "last" l avant dernier token "prev_last" :
**		si last est un '&&' ';' ou un connerie du genre -> completion binaire sur le mot d apres
**		si prev
**	
*/

char	**comple_matching(t_line *line, t_comple *c)
{
	t_lexer		lex;
	t_list		*last;
//	t_list		*prev_last;
	t_list		*token_list;
	char		*current_word;
	
	(void)c;
	lex = init_lexer(line->buff);
	token_list = start_lex(&lex);
	//lexer_debug(token_list);
	printf("\n%s|\n", line->buff);
	printf("\n%d\n", line->pos);
	if (line->pos == 0 || (line->pos > 0 && (line->buff[line->pos] == ' ' || line->buff[line->pos] == '\0') && line->buff[line->pos - 1] == ' ')) // cas 1.
	{
		last = ft_last_simple_lst(token_list);
		current_word = get_current_word_cursor(line);
		if (!last || (last && ((t_token *)last->data)->id == 0))
		{
			printf("\ncomple file matches\n");
			return (comple_file_matches(line, c, current_word));
		}
		else
		{
			printf("\ncomple bin  matches\n");
			return (NULL); //comple bin
		}
	}
	printf("\ncomple bin  matches\n");
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
	c->max_len = ft_arraymax_f((const char**)c->matches, ft_strlen);
	c->nb_matches = ft_arraylen((const char**)c->matches);
	comple_init_winch(c);
	c->pos = -1;
	if (c->nb_matches == 1)
	{
		c->pos = 0;
		comple_exit_matched(line, *c, 0);
		return (0);
	}
	else if (c->nb_matches == 0)
		return (0);
	return (1);
}
