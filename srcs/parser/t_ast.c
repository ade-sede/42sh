/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*new_ast(t_token *token, int symbol)
{
	t_ast	*new;

	new = ft_memalloc(sizeof(t_ast));
	new->token = token;
	new->symbol = symbol;
	return (new);
}

t_ast	*dup_ast(t_ast *ast)
{
	int		i;
	t_ast	*new;

	i = 0;
	if (!ast)
		return (NULL);
	if (ast->token)
		new = new_ast(dup_token(ast->token), 0);
	else if (ast->symbol > 0)
		new = new_ast(NULL, ast->symbol);
	while (ast->child[i] && i < 7)
	{
		new->child[i] = dup_ast(ast->child[i]);
		i++;
	}
	return (new);
}

void	free_ast(t_ast *ast)
{
	int		i;

	i = 0;
	if (!ast)
		return ;
	while (ast->child[i] && i < 7)
	{
		free_ast(ast->child[i]);
		i++;
	}
	free(ast->heredoc);
	free(ast);
}

void	free_ast_and_token(t_ast *ast)
{
	int		i;

	i = 0;
	if (!ast)
		return ;
	while (ast->child[i] && i < 7)
	{
		free_ast(ast->child[i]);
		i++;
	}
	if (ast->token)
		free_token(ast->token);
	free(ast);
}
