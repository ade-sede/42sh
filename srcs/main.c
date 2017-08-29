/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:03:41 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/29 02:37:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"
#include "completion.h"

int	main(void)
{
	extern const char	**environ;

	env_load_base_env(singleton_env(), environ);
	create_ternary_tree(singleton_env());
	history_load(singleton_hist(), singleton_env());
	conf_term_in();
	main_loop(singleton_env());
	env_free_env(singleton_env());
	return (0);
}
