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
		int cmd_name_open)
{

	char		**res;
//	t_list		*glob_list;

	/*
**		if (glob_list = pathname_expansion(token, 0)))
**			res = comple_globing_matches(line, c, glob_list);
*/
	if (!ft_strchr(c->current_word, '/') && !cmd_name_open)
		res = comple_bin_matches(line, c);
	else
		res = comple_file_matches(line, c);
	return (res);

	return (NULL);
}

int		lex_completion(t_line *line)
{
	t_lexer		lex;
	char		line_pos_char;
	int			cmd_name_open;
	t_list		*token_list = NULL;

	line_pos_char = line->buff[line->pos]; //TODO: attention peut etre que line-buff + line-pos point sur le \0
	line->buff[line->pos] = '\0';
	init_lexer(&lex, line->buff);
	get_token_list(&lex, &token_list, singleton_env()->alias);
	line->buff[line->pos] = line_pos_char;
	cmd_name_open = lex.cmd_name_open;
	remove_lexer(&lex, &token_list);
	return (cmd_name_open);
}

char			**comple_matching(t_line *line, t_comple *c)
{
	char		**res;
	int			cmd_name_open;

	c->to_replace = get_start_word_cursor(line);
	cmd_name_open = lex_completion(line);
	res = NULL;
	c->current_word = get_current_word_cursor(line);
	if (line->pos == 0 || (line->pos > 0 && (line->buff[line->pos] == ' '
					|| line->buff[line->pos] == '\0')
				&& line->buff[line->pos - 1] == ' '))
		res = comple_matching_no_cursorword(line, c, cmd_name_open);
	else
		res = comple_matching_cursorword(line, c, cmd_name_open);
	free(c->current_word);
	return (res);
}
