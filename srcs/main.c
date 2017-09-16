/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:36 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 03:09:19 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"
#include "completion.h"
#include "get_next_line.h"
#include "color.h"

int	main(void)
{
	extern const char	**environ;
	t_env				*env;

	env = singleton_env();
	env_load_base_env(env, environ);
	create_ternary_tree(env);
	history_load(singleton_hist(), env);
	conf_term_in();
	main_loop(env);
	env_free_env(env);
	return (0);
}
