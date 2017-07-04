/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:22:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/04 16:01:19 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "color.h"
#include "lexer.h"
#include "parser.h"

/*
**	Going to send a line to the lexer and print the output top to bottom (last
**	token first)
*/

static void	read_tree(t_ast *ast_start)
{
	size_t	index;
	t_token	*token_parent;
	char	*parent_name;

	index = 0;
	token_parent = ast_start->token;
	printf(GRN"NODE = "RESET);
	if (token_parent)
		parent_name = token_parent->value;
	else
	{
		if (ast_start->symbol == SIMPLE_COMMAND)
			parent_name = "SIMPLE_COMMAND";
		if (ast_start->symbol == IO_REDIRECT)
			parent_name = "IO_REDIRECT";
	}
	printf(MAG"#"CYN"%s"MAG"#"RESET""YEL"(%d)\n"RESET, parent_name, ast_start->symbol);
	while (ast_start->child)
	{
		printf(RED"Starting treatment of child nb "BLU"%zu"RESET" of parent "MAG"#"CYN"%s"MAG"#"YEL"(%d)\n"RESET, index, parent_name, ast_start->symbol);
		read_tree(ast_start->child->data);
		printf(PNK"\nBACK TO PARENT -> "RESET"Current node = "CYN"%s"RESET" !!!\n", parent_name);
		ast_start->child = ast_start->child->next;
		index++;
	}
}

int		main(void)
{
	t_ast	*ast_start;
	char	buff[4096];
	t_lexer	lex;

	ft_putstr("Give me a string > ");
	read(0, buff, 4096);
	*strchr(buff, '\n') = 0;
	if (strchr(buff, '\n') != NULL)
		printf(RED"Found a newline in the buff\n"RESET);
	lex = init_lexer(buff);
	ast_start = start_lex(&lex);
	printf(RED"-------------------------------------------\n"RESET);
	printf("RESULTS !!!\n");
	printf("Reading the tree, left recursive\n");
	printf(RED"-------------------------------------------\n"RESET);
	read_tree(ast_start);
	return (0);
}
