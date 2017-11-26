/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:49 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ncurses.h>

void	aux(t_btree *root, int li, int co, void (printer) (void *))
{
	if (!root)
		return ;
	move(li, co);
	printer(root->data);
	aux(root->left, li + 2, co - 10, printer);
	aux(root->right, li + 2, co + 10, printer);
}

void	btree_print(t_btree *root, void (printer) (void *))
{
	if (!root)
		return ;
	aux(root, 0, COLS / 3, printer);
}
