/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"
#include "environ.h"

int		parse_tilde(t_expand *exp)
{
	char	*home;

	home = env_getenv((const char **)singleton_env()->environ, "HOME", NULL);
	if (!(home != NULL && *home))
		home = ft_gethome();
	w_addstr(&exp->word, home);
	w_addstr(&exp->g_word, home);
	return (1);
}
