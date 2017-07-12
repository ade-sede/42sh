/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tild_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 13:10:07 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/12 11:00:30 by ade-sede         ###   ########.fr       */
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


	index_space = 0;
	index_slash = 0;
	split_space = NULL;
	split_slash = NULL;
	if (token->type != QUOTED)
	{
		split_space = ft_strsplit_keep(token->value, WHITESPACES);
		/* Removing old value of token->value */
		token->value = ft_strchange(token->value, ft_strnew(0));
		while (split_space[index_space])
		{
#ifdef TILD_DEBUG
			printf(RED"-----------------------------------------------------\n"RESET);//			REMOVE		
			printf(GRN"Split_space[%zu] = "MAG"#"CYN"%s"MAG"#\n"RESET, index_space, split_space[index_space]);//			REMOVE		
#endif
			if (ft_strchr(split_space[index_space], '/'))
			{
				split_slash = ft_strsplit_keep(split_space[index_space], "/");
				/* Removing old value, reinitialising before join */
				split_space[index_space] = ft_strchange(split_space[index_space], ft_strnew(0));
				while (split_slash[index_slash])
				{
#ifdef TILD_DEBUG
					printf(GRN"-----------------------------------------------------\n"RESET);//			REMOVE		
					printf(PNK"Split_slash[%zu] = "MAG"#"CYN"%s"MAG"#\n"RESET, index_slash, split_slash[index_slash]);//			REMOVE		
#endif
					if (index_slash == 0 && *(split_slash[index_slash]) == '~')
					{
						split_slash[index_slash] = ft_strchange(split_slash[index_slash], ft_strdup(env_getenv((const char **)env->environ, "HOME", NULL)));
#ifdef TILD_DEBUG
						printf(PNK"Split_slash[%zu]"RED" CHANGED VALUE !!!\n"RESET, index_slash);//			REMOVE		
						printf(PNK"Split_slash[%zu] IS NOW "MAG"#"CYN"%s"MAG"#\n"RESET, index_slash, split_slash[index_slash]);//			REMOVE		
#endif
					}
					/* Rejoining mini strings to recreate the string above */
					split_space[index_space] = ft_strchange(split_space[index_space], ft_strjoin(split_space[index_space], split_slash[index_slash]));
#ifdef TILD_DEBUG
					printf(RED"Appending split_slash[%zu] to the split_space[%zu]\n"RESET, index_slash, index_space);
					printf(GRN"Split_space[%zu] IS NOW "MAG"#"CYN"%s"MAG"#\n"RESET, index_space, split_space[index_space]);
#endif
					free(split_slash[index_slash]);
					index_slash++;
				}
			}
			else if (ft_strequ(split_space[index_space], "~"))
				split_space[index_space] = ft_strchange(split_space[index_space], ft_strdup(env_getenv((const char **)env->environ, "HOME", NULL)));
			free(split_slash);
			/* Rejoining mini strings to recreate the string above */
			token->value = ft_strchange(token->value, ft_strjoin(token->value, split_space[index_space]));
#ifdef TILD_DEBUG
			printf(GRN"Appending split_space[%zu] to token->value\n"RESET, index_space);
			printf(GRN"token->value IS NOW "MAG"#"CYN"%s"MAG"#\n"RESET, token->value);
#endif
			free(split_space[index_space]);
			index_space++;
		}
		free(split_space);
	}
}
