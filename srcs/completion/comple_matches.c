#include "lexer.h"
#include "completion.h"
#include <stdio.h>

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

t_token			*lex_completion(t_lexer *lex)
{
	t_token	*token;
	t_token	*prev_token;
	int		reopen;

	prev_token = NULL;
	while ((token = start_lex(lex, &reopen)) != NULL)
	{
		free_token(prev_token);
		prev_token = token;
	}
	return (prev_token);
}

char			**comple_matching_no_cursorword(t_line *line, t_comple *c,
		t_lexer lex)
{
	char		**res;

	if (!lex.cmd_name_open)
		res = comple_file_matches(line, c);
	else
		res = comple_bin_matches(line, c);
	return (res);
}

char			**comple_matching_cursorword(t_line *line, t_comple *c,
		t_token *token)
{
	char		**res;
	t_list		*glob_list;

	if (token != NULL && (glob_list = pathname_expansion(token, 0)))
		res = comple_globing_matches(line, c, glob_list);
	else if (!ft_strchr(c->current_word, '/') && token != NULL && \
			token->cmd_name == 1)
		res = comple_bin_matches(line, c);
	else
		res = comple_file_matches(line, c);
	return (res);
}

char			**comple_matching(t_line *line, t_comple *c)
{
	char		**res;
	t_lexer		lex;
	t_token		*token;

	c->to_replace = get_start_word_cursor(line);
	lex = get_lex_line_cursor(line);
	token = lex_completion(&lex);
	res = NULL;
	c->current_word = get_current_word_cursor(line);
	if (line->pos == 0 || (line->pos > 0 && (line->buff[line->pos] == ' '
			|| line->buff[line->pos] == '\0')
						&& line->buff[line->pos - 1] == ' '))
		res = comple_matching_no_cursorword(line, c, lex);
	else
		res = comple_matching_cursorword(line, c, token);
	free(lex.line);
	free(c->current_word);
	free_token(token);
	return (res);
}
