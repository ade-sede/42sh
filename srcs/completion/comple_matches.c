/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_matches.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:07:47 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**comple_matching_no_cursorword(t_line *line, t_comple *c)
{
	t_lexer		lex;
	t_list		*last;
	t_list		*token_list;
	char		**res;

	lex = init_lexer(line->buff);
	token_list = start_lex(&lex);
	last = ft_last_simple_lst(token_list);
	if (!last || (last && ((t_token *)last->data)->id == 0))
		res = comple_file_matches(line, c);
	else
		res = comple_bin_matches(line, c);
	free_token_list(token_list);
	return (res);
}

char	**comple_matching_cursorword(t_line *line, t_comple *c)
{
	t_lexer		lex;
	t_list		*token_list;
	t_list		*last;
	t_list		*prev_last;
	char		**res;

	lex = init_lexer(line->buff);
	token_list = start_lex(&lex);
	last = ft_last_simple_lst(token_list);
	if (!token_list->next)
		res = comple_bin_matches(line, c);
	else
	{
		prev_last = ft_previous_last_simple_lst(token_list);
		if (((t_token *)prev_last->data)->id == 0)
			res = comple_file_matches(line, c);
		else
			res = comple_bin_matches(line, c);
	}
	free_token_list(token_list);
	return (res);
}

char	**comple_matching(t_line *line, t_comple *c)
{
	c->current_word = get_current_word_cursor(line);
	if (line->pos == 0 || (line->pos > 0 && (line->buff[line->pos] == ' '
			|| line->buff[line->pos] == '\0')
						&& line->buff[line->pos - 1] == ' '))
		return (comple_matching_no_cursorword(line, c));
	else
		return (comple_matching_cursorword(line, c));
	return (NULL);
}
