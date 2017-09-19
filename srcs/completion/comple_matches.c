#include "lexer.h"
#include "completion.h"

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
**		si last est un '&&' ';' ou un connerie du genre ->
**		completion binaire sur le mot d apres
**		si prev
*/

char			**comple_matching_no_cursorword(t_line *line, t_comple *c)
{
	t_lexer		lex;
	t_list		*token_list;
	char		**res;
	char		line_pos_char;

	line_pos_char = line->buff[line->pos];
	line->buff[line->pos] = '\0';
	lex = init_lexer(line->buff);
	lex.reopen = 0;
	token_list = start_lex(&lex);
	if (!token_list || (lex.cmd_name_open && !TK_IS_REDIR(lex.last_id)))
		res = comple_bin_matches(line, c);
	else
		res = comple_file_matches(line, c);
	free_token_list(token_list);
	line->buff[line->pos] = line_pos_char;
	return (res);
}

static t_lexer	get_lex_line_cursor(t_line *line)
{
	char		line_pos_char;
	t_lexer		lex;

	line_pos_char = line->buff[line->pos];
	line->buff[line->pos] = '\0';
	lex.reopen = 0;
	lex = init_lexer(line->buff);
	line->buff[line->pos] = line_pos_char;
	return (lex);
}

char			**comple_matching_cursorword(t_line *line, t_comple *c)
{
	t_lexer		lex;
	t_list		*token_list;
	t_list		*last;
	t_token		*token;
	char		**res;

	lex = get_lex_line_cursor(line);
	token_list = start_lex(&lex);
	last = ft_last_simple_lst(token_list);
	if (ft_strchr(c->current_word, '/'))
		res = comple_file_matches(line, c);
	else if (!token_list->next)
		res = comple_bin_matches(line, c);
	else
	{
		token = last->data;
		if (token->cmd_name)
			res = comple_bin_matches(line, c);
		else
			res = comple_file_matches(line, c);
	}
	free_token_list(token_list);
	return (res);
}

char			**comple_matching(t_line *line, t_comple *c)
{
	c->current_word = get_current_word_cursor(line);
	if (line->buff[line->pos] == '*' || \
			(line->pos != 0 && line->buff[line->pos - 1] == '*'))
		return (comple_globing_matches(line, c));
	else if (line->pos == 0 || (line->pos > 0 && (line->buff[line->pos] == ' '
			|| line->buff[line->pos] == '\0')
						&& line->buff[line->pos - 1] == ' '))
		return (comple_matching_no_cursorword(line, c));
	else
		return (comple_matching_cursorword(line, c));
	return (NULL);
}
