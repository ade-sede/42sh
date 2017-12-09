/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/09 17:24:21 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "exec.h"

static t_exec_func	g_exec_func[] =
{
	{PROGRAM, &exec_program},
	{COMPLETE_COMMANDS, &exec_complete_commands},
	{COMPLETE_COMMAND, &exec_complete_command},
	{LIST, &exec_list},
	{AND_OR, &exec_and_or},
	{PIPELINE, &exec_pipeline},
	{PIPE_SEQUENCE, &exec_pipe_sequence},
	{COMMAND, &exec_command},
	{COMPOUND_COMMAND, &exec_compound_command},
	{SUBSHELL, &exec_subshell},
	{COMPOUND_LIST, &exec_compound_list},
	{TERM, &exec_term},
	{FOR_CLAUSE, &exec_for_clause},
	{CASE_CLAUSE, &exec_case_clause},
	{IF_CLAUSE, &exec_if_clause},
	{ELSE_PART, &exec_else_part},
	{WHILE_CLAUSE, &exec_while_clause},
	{UNTIL_CLAUSE, &exec_until_clause},
	{FUNCTION_DEFINITION, &exec_function_definition},
	{FUNCTION_BODY, &exec_function_body},
	{DO_GROUP, &exec_do_group},
	{BRACE_GROUP, &exec_brace_group},
	{SIMPLE_COMMAND, &exec_simple_command},
	{0, NULL},
};

int		exec(t_ast *ast)
{
	int		i;

	i = 0;
	while (g_exec_func[i].f)
	{
		if (ast->symbol == (int)g_exec_func[i].symbol)
			return (g_exec_func[i].f(ast));
		i++;
	}
	debug_symbol(ast);
	ft_dprintf(2, "error : symbol not recognized by exec function\n");
	return (1);
}
