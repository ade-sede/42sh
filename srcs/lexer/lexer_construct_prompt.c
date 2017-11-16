#include "lexer.h"
#include "libft.h"
#include <stdio.h>

struct s_state_to_prompt	g_state_to_promt[] =
{
//	{${,"braceparam"},
	{CMD_SUBST,"cmdsubst"},
	{AR_EXP, "mathsubst"},
	{DQUOTES,"dquote"},
	{QUOTES,"quote"},
	{-1, NULL},
};

char	*lexer_construct_prompt(t_lexer *lex)
{
	int		state;

	state = ((struct s_info*)lex->state->data)->state;
	int	i = 0;
	while (g_state_to_promt[i].string)
	{
		if (state == g_state_to_promt[i].id) 
			return (ft_strdup(g_state_to_promt[i].string));
		i++;
	}
	return (NULL);
}

