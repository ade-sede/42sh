#include "syntax_coloring.h"
#include "libft.h"
#include "lexer.h"

static char	*g_operator_list[] =
{
	"<",
	"<<",
	">",
	";",
	"|",
	"&",
	"&&",
	"||",
	";;",
	"<<",
	">>",
	"<&",
	">&",
	"<>",
	"<<-",
	">|",
	NULL
};

int		lex_action_operator_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	char	*operator_string;
	ssize_t	*info;
	size_t	i;

	i = 0;
	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
	{
		pop_state_le(lex, state_info);
		return (TRUE);
	}
	operator_string = ft_strsub(lex->line, info[_T_START], info[_T_COUNT] + 1);
	while (g_operator_list[i] && !ft_strequ(g_operator_list[i], operator_string))
		++i;
	if (g_operator_list[i])
		consume_input_le(lex, line);
	else
		pop_state_le(lex, state_info);
	return (TRUE);
}
