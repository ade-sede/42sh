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

int		lex_action_operator(t_lexer *lex, struct s_info **state_info)
{
	char	*operator_string;
	struct s_info *info;
	size_t	i;

	i = 0;
	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
	{
		pop_state(lex, state_info);
		return (TRUE);
	}
	operator_string = ft_strnew(info->count + 1);
	ft_memcpy(operator_string, info->value.str, info->count);
	operator_string[info->count] = lex->line[lex->pos];
	while (g_operator_list[i] && !ft_strequ(g_operator_list[i], operator_string))
		++i;
	if (g_operator_list[i])
		consume_input(lex);
	else
		pop_state(lex, state_info);
	free(operator_string);
	return (TRUE);
}
