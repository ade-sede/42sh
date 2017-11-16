#include "syntax_coloring.h"
#include "libft.h"

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
	{CMD_SUBST, &lex_action_cmd_subst_le},
};

static int	(*get_action_le(ssize_t state))(t_lexer *, ssize_t **, t_line *)
{
	size_t	i;

	i = 0;
	while (g_lex_action_le[i].state != state)
		++i;
	return (g_lex_action_le[i].func);
}

int		delim(t_lexer *lex, t_line *line)
{
	ssize_t	*state_info = NULL;
	int		ret = 1;
	/*
	**	while we didnt finish a token or reach critical end, keep going.
	*/
	while (ret && !(state_info && state_info[_T_END] != -1 && ((ssize_t*)lex->state->data)[_T_STATE] == DEFAULT))
		ret = get_action_le(((ssize_t*)lex->state->data)[_T_STATE])(lex, &state_info, line);
	free(state_info);
	if (((ssize_t*)lex->state->data)[_T_STATE] != DEFAULT)
		return (0);
	return (1);
}
