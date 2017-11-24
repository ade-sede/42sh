/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>

void		free_ast_node(void *ast_node)
{
	free_ast(((t_ast_lst *)ast_node)->ast);
}

t_state_lst	*new_state_lst(int n)
{
	t_state_lst *new;

	new = ft_memalloc(sizeof(t_state_lst));
	new->state = n;
	return (new);
}

t_ast_lst	*new_ast_lst(t_ast *ast)
{
	t_ast_lst *new;

	new = ft_memalloc(sizeof(t_ast_lst));
	new->ast = ast;
	return (new);
}
