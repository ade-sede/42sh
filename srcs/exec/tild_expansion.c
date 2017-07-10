/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tild_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 13:10:07 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/10 16:59:10 by ade-sede         ###   ########.fr       */
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

void	tild_expand(t_env *env, t_token *token)
{
	char	**split_space;
	char	**split_slash;
	size_t	index_space;
	size_t	index_slash;

	(void)env;
	index_space = 0;
	index_slash = 0;
	split_space = NULL;
	split_slash = NULL;
	if (token->type != QUOTED)
	{
		split_space = ft_strsplit_keep(token->value, WHITESPACES);
		token->value = ft_strchange(token->value, ft_strnew(0));
		while (split_space[index_space])
		{
			split_slash = ft_strsplit(split_space[index_space], "/");
			split_space[index_space] = ft_strchange(split_space[index_space], ft_strnew(0));
			while (split_slash && split_slash[index_slash])
			{
				if (*(split_slash[index_slash]) == '~')
				{
					split_slash[index_slash] = ft_strchange(token->value, ft_strdup(env_getenv((const char**)env->environ, "HOME", NULL)));
					printf("Split_slash =" MAG"#"CYN"%s"MAG"#\n"RESET, split_slash[index_slash]);//			REMOVE		
				}
				printf("Split space =" MAG"#"CYN"%s"MAG"#\n"RESET, split_space[index_space]);//			REMOVE		
				split_space[index_space] = ft_strchange(split_space[index_space], ft_strjoin(split_space[index_space], split_slash[index_slash]));
				/* free(split_slash[index_slash]); */
				index_slash++;
			}
			token->value = ft_strchange(token->value, ft_strjoin(token->value, split_space[index_space]));
			printf("Token->value =" MAG"#"CYN"%s"MAG"#\n"RESET, token->value);//			REMOVE		
			/* free(split_space[index_space]); */
			index_space++;
		}
	}
}
