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

char			**comple_matching_no_cursorword(t_line *line, t_comple *c,
		int cmd_name_open)
{
	char		**res;

	if (!cmd_name_open)
		res = comple_file_matches(line, c);
	else
		res = comple_bin_matches(line, c);
	return (res);
}

char			**comple_matching_cursorword(t_line *line, t_comple *c,
		int cmd_name)
{
	char		**res;

	if (!cmd_name || ft_strchr(c->current_word, '/'))
		res = comple_file_matches(line, c);
	else
		res = comple_bin_matches(line, c);
	return (res);
}

int				lex_completion(t_line *line, int *cmd_name_open)
{
	t_lexer		lex;
	char		line_pos_char;
	t_list		*token_list;
	t_list		*last;
	int			cmd_name;

	token_list = NULL;
	cmd_name = 1;
	line_pos_char = line->buff[line->pos];
	line->buff[line->pos] = '\0';
	init_lexer(&lex, line->buff);
	get_token_list(&lex, &token_list, singleton_env()->alias);
	line->buff[line->pos] = line_pos_char;
	*cmd_name_open = lex.cmd_name_open;
	last = ft_last_simple_lst(token_list);
	if (last && last->data)
		cmd_name = ((t_token *)last->data)->cmd_name;
	remove_lexer(&lex, &token_list);
	return (cmd_name);
}

char			**comple_matching(t_line *line, t_comple *c)
{
	char		**res;
	int			cmd_name_open;
	int			cmd_name;

	c->to_replace = get_start_word_cursor(line);
	cmd_name = lex_completion(line, &cmd_name_open);
	res = NULL;
	c->current_word = get_current_word_cursor(line);
	if (line->pos == 0 || (line->pos > 0 && (line->buff[line->pos] == ' '
					|| line->buff[line->pos] == '\0')
				&& line->buff[line->pos - 1] == ' '))
		res = comple_matching_no_cursorword(line, c, cmd_name_open);
	else
		res = comple_matching_cursorword(line, c, cmd_name);
	free(c->current_word);
	return (res);
}
