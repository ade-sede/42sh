/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tild_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"

/*
**		LEAKS
*/

static void	split_on_slash(t_env *env, char **split_space, size_t index_space)
{
	char	**split_slash;
	size_t	index_slash;

	split_slash = NULL;
	index_slash = 0;
	split_slash = ft_strsplit_keep(split_space[index_space], "/");
	split_space[index_space] = ft_strchange(split_space[index_space], \
			ft_strnew(0));
	while (split_slash[index_slash])
	{
		if (index_slash == 0 && *(split_slash[index_slash]) == '~')
			split_slash[index_slash] = ft_strchange(split_slash[index_slash], \
			ft_strdup(env_getenv((const char **)env->environ, "HOME", NULL)));
		split_space[index_space] = ft_strchange(split_space[index_space], \
				ft_strjoin(split_space[index_space], split_slash[index_slash]));
		free(split_slash[index_slash]);
		index_slash++;
	}
	free(split_slash);
}

static void	split_on_space(t_env *env, t_token *token)
{
	char	**split_space;
	size_t	index_space;

	split_space = NULL;
	index_space = 0;
	split_space = ft_strsplit_keep(token->value, WHITESPACES);
	token->value = ft_strchange(token->value, ft_strnew(0));
	while (split_space[index_space])
	{
		if (ft_strchr(split_space[index_space], '/'))
			split_on_slash(env, split_space, index_space);
		else if (ft_strequ(split_space[index_space], "~"))
			split_space[index_space] = ft_strchange(split_space[index_space], \
			ft_strdup(env_getenv((const char **)env->environ, "HOME", NULL)));
		token->value = ft_strchange(token->value, ft_strjoin(token->value, \
					split_space[index_space]));
		free(split_space[index_space]);
		index_space++;
	}
	free(split_space);
}

void		tild_expand(t_env *env, t_token *token)
{
	if (token->type != QUOTED)
		if (ft_strchr(token->value, '~'))
			split_on_space(env, token);
}
