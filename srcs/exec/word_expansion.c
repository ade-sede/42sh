#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"

/*
**	TODO : A function to check if the token is subject to param expansion. Atm
**	we're doing quote removal first, cus its easier, but that should come last
*/


t_list	*propRe(t_list *list)
{
	t_list	*first = NULL;

	first = list;
	while (list)
	{
		list->data = create_token(list->data, 0, 0);
		list = list->next;
	}
	return (first);
}

t_list	*pathname_expansion(t_token *token)
{
	t_list	*first;

	first = NULL;
	if (token->type != QUOTED && token->type != DQUOTED)
	{
		if (ft_strchr(token->value, '*') || ft_strchr(token->value, '['))
			first = propRe(glob(token->value));
		else if (ft_strchr(token->value, '{'))
			first = propRe(expand_curly_brackets(token->value));
	if (first != NULL)
		free_token(token);
	}
	return (first);
}

t_list	*exec_expand(t_token *token)
{
	t_env	*env;
	t_list	*node;

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
		{
			if (ft_strchr(token->value, '~'))
				tild_expand(env, token);
		}
		parameter_expansion(env, token);
	}
	if ((node = pathname_expansion(token)) == NULL)
		node = ft_simple_lst_create(token);
	return (node);
}
