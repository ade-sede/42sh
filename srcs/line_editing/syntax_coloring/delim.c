/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 12:26:09 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:55:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_coloring.h"
#include "libft.h"
#include "lexer.h"

static struct s_lex_action_le g_lex_action_le[] =
{
	{DEFAULT, &lex_action_default_le},
	{WORD, &lex_action_word_le},
	{WHITESPACE, &lex_action_whitespace_le},
	{QUOTES, &lex_action_quotes_le},
	{DQUOTES, &lex_action_dquotes_le},
	{BS, &lex_action_bs_le},
	{OPERATOR, &lex_action_operator_le},
	{NEWLINE, &lex_action_newline_le},
	{COMMENT, &lex_action_comment_le},
	{PARAM_EXP, &lex_action_param_exp_le},
	{AR_EXP, &lex_action_ar_exp_le},
	{CMD_SUBST, &lex_action_cmd_subst_le},
};

static int	(*gale(ssize_t state))(t_lexer *, struct s_info **, t_line *)
{
	size_t	i;

	i = 0;
	while (g_lex_action_le[i].state != state)
		++i;
	return (g_lex_action_le[i].func);
}

int			delim(t_lexer *lex, t_line *line)
{
	struct s_info	*state_info;
	t_token			*token;
	int				ret;

	ret = TRUE;
	token = NULL;
	state_info = NULL;
	while (ret)
	{
		if (((struct s_info*)lex->state->data)->state == DEFAULT)
			if (state_info && state_info->count != 0)
				break ;
		ret = \
	gale(((struct s_info*)lex->state->data)->state)(lex, &state_info, line);
	}
	free_info(state_info);
	if (((struct s_info*)lex->state->data)->state != DEFAULT)
		return (0);
	return (1);
}
