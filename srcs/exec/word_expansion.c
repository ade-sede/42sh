#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"

/*
**	TODO : A function to check if the token is subject to param expansion. Atm
**	we're doing quote removal first, cus its easier, but that should come last
*/

void		exec_expand(t_token *token)
{
	t_env	*env;

	env = singleton_env();
	if (token->type == DQUOTED || token->type == QUOTED)
	{
		*token->value = 0;
		if (token->size > 2)
			token->value = ft_strchange(token->value, \
					ft_strsub(token->value, 1, token->size - 2));
		token->size -= 2;
	}
	if (token->type != QUOTED)
	{
		if (token->type != DQUOTED)
			if (ft_strchr(token->value, '~'))
				tild_expand(env, token);
		parameter_expansion(env, token);
	}
}
