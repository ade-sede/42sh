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

#include <stdio.h>
static t_list	*get_globbed_tokens(t_list *list)
{
	t_list	*first;

	first = list;
	while (list)
	{
		list->data = create_token(list->data, 0, 0);
		list = list->next;
	}
	return (first);
}

/*
**	if (ft_strchr(token->value, '*') || ft_strchr(token->value, '['))
**	first = get_globbed_tokens(glob(token->value));
**	else if (ft_strchr(token->value, '{'))
**	first = get_globbed_tokens(expand_curly_brackets(token->value));
**	if (first != NULL)
**	free_token(token);
*/

t_list	*pathname_expansion(t_token *token, int match_all)
{
	t_list	*glob_ret;
	t_list	*gen;
	t_list	*ret;
	t_token	*token_gen;
	t_list	*glob_list;

	ret = NULL;
	if (!ft_strchr(token->value, '*') && !ft_strchr(token->value, '[') && !ft_strchr(token->value, '{'))
		return (NULL);
	if (token->type != QUOTED && token->type != DQUOTED)
	{
		gen = get_globbed_tokens(expand_curly_brackets(token->value));
		while (gen)
		{
			token_gen = gen->data;
//			dprintf(2, MAG"#"CYN"%s"MAG"#\n"RESET, token_gen->value);//			REMOVE		
			if (!(glob_list = glob(token_gen->value)) && match_all)
				glob_list = ft_simple_lst_create(ft_strdup(token_gen->value));
			glob_ret = get_globbed_tokens(glob_list);
			if (glob_ret)
				ft_simple_lst_pushback(&ret, glob_ret);
			ft_simple_lst_del_one(&gen, gen, free_token);
		}
		free_token(token);
	}
	return (ret);
}

t_list			*exec_expand(t_token *token)
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
		{
			if (ft_strchr(token->value, '~'))
				tild_expand(env, token);
		}
		parameter_expansion(env, token);
	}
	return (pathname_expansion(token, 1));
}
