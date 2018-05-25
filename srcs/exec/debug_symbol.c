/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2018/05/25 20:41:13 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>
#include "exec.h"

struct s_sym_to_string	sts[] = {
	{PROGRAM, "PROGRAM"},
	{COMPLETE_COMMANDS, "COMPLETE_COMMANDS"},
	{COMPLETE_COMMAND, "COMPLETE_COMMAND"},
	{LIST, "LIST"},
	{AND_OR, "AND_OR"},
	{PIPELINE, "PIPELINE"},
	{PIPE_SEQUENCE, "PIPE_SEQUENCE"},
	{COMMAND, "COMMAND"},
	{COMPOUND_COMMAND, "COMPOUND_COMMAND"},
	{SUBSHELL, "SUBSHELL"},
	{COMPOUND_LIST, "COMPOUND_LIST"},
	{TERM, "TERM"},
	{FOR_CLAUSE, "FOR_CLAUSE"},
	{NAME, "NAME"},
	{SYM_IN, "SYM_IN"},
	{WORDLIST, "WORDLIST"},
	{CASE_CLAUSE, "CASE_CLAUSE"},
	{CASE_LIST_NS, "CASE_LIST_NS"},
	{CASE_LIST, "CASE_LIST"},
	{CASE_ITEM_NS, "CASE_ITEM_NS"},
	{CASE_ITEM, "CASE_ITEM"},
	{PATTERN, "PATTERN"},
	{IF_CLAUSE, "IF_CLAUSE"},
	{ELSE_PART, "ELSE_PART"},
	{WHILE_CLAUSE, "WHILE_CLAUSE"},
	{UNTIL_CLAUSE, "UNTIL_CLAUSE"},
	{FUNCTION_DEFINITION, "FUNCTION_DEFINITION"},
	{FUNCTION_BODY, "FUNCTION_BODY"},
	{FNAME, "FNAME"},
	{BRACE_GROUP, "BRACE_GROUP"},
	{DO_GROUP, "DO_GROUP"},
	{SIMPLE_COMMAND, "SIMPLE_COMMAND"},
	{CMD_PREFIX, "CMD_PREFIX"},
	{CMD_SUFFIX, "CMD_SUFFIX"},
	{CMD_NAME, "CMD_NAME"},
	{CMD_WORD, "CMD_WORD"},
	{REDIRECT_LIST, "REDIRECT_LIST"},
	{IO_REDIRECT, "IO_REDIRECT"},
	{IO_FILE, "IO_FILE"},
	{FILENAME, "FILENAME"},
	{IO_HERE, "IO_HERE"},
	{HERE_END, "HERE_END"},
	{NEWLINE_LIST, "NEWLINE_LIST"},
	{LINEBREAK, "LINEBREAK"},
	{SEPARATOR_OP, "SEPARATOR_OP"},
	{SEPARATOR, "SEPARATOR"},
	{SEQUENTIAL_SEP, "SEQUENTIAL_SEP"},
	{0, NULL}
};

void	debug_symbol(t_ast *ast)
{
	int	i;

	i = 0;
	while (sts[i].string)
	{
		if (ast->symbol == (int)sts[i].symbol)
		{
			ft_dprintf(2, "%s\n", sts[i].string);
			return ;
		}
		i++;
	}
}
