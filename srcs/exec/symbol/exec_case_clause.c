/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_case_clause.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:06 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** case_clause      : Case WORD linebreak in linebreak case_list    Esac
**                  | Case WORD linebreak in linebreak case_list_ns Esac
**                  | Case WORD linebreak in linebreak              Esac
**                  ;
** case_item_ns     :     pattern ')' linebreak
**                  |     pattern ')' compound_list
**                  | '(' pattern ')' linebreak
**                  | '(' pattern ')' compound_list
**                  ;
** case_item        :     pattern ')' linebreak     DSEMI linebreak
**                  |     pattern ')' compound_list DSEMI linebreak
**                  | '(' pattern ')' linebreak     DSEMI linebreak
**                  | '(' pattern ')' compound_list DSEMI linebreak
**                  ;
** pattern          :             WORD
**                  | pattern '|' WORD
*/

int		exec_pattern(t_ast *ast, char *word)
{
	if (is_token(ast->child[0], TK_WORD))
		return (ft_strequ(word, ast->child[0]->token->value));
	if (ft_strequ(word, ast->child[2]->token->value))
		return (1);
	else
		return (exec_pattern(ast->child[0], word));
}

int		exec_case_item(t_ast *ast, char *word, int *patern_found)
{
	t_ast	*pattern;
	t_ast	*compound_list;

	compound_list = NULL;
	pattern = is_symb(ast->child[0], PATTERN) ? ast->child[0] : ast->child[1];
	if (is_symb(ast->child[2], COMPOUND_LIST))
		compound_list = ast->child[2];
	else if (is_symb(ast->child[3], COMPOUND_LIST))
		compound_list = ast->child[3];
	if (exec_pattern(pattern, word))
	{
		*patern_found = 1;
		if (compound_list)
			return (exec(compound_list));
	}
	return (EXIT_SUCCESS);
}

/*
** case_list_ns     : case_list case_item_ns
**                  |           case_item_ns
**                  ;
** case_list        : case_list case_item
**                  |           case_item
**                  ;
*/

int		exec_case_list(t_ast *ast, char *word, int *pattern_found)
{
	int		exit_status;

	if (is_symb(ast->child[0], CASE_ITEM) || is_symb(ast->child[0],
				CASE_ITEM_NS))
		return (exec_case_item(ast->child[0], word, pattern_found));
	exit_status = exec_case_list(ast->child[0], word, pattern_found);
	if (*pattern_found)
		return (exit_status);
	return (exec_case_item(ast->child[1], word, pattern_found));
}

int		exec_case_clause(t_ast *ast)
{
	char	*word;
	int		pattern_found;

	pattern_found = 0;
	word = ast->child[1]->token->value;
	if (is_token(ast->child[5], TK_ESAC))
		return (EXIT_SUCCESS);
	else if (is_symb(ast->child[5], CASE_LIST_NS) || is_symb(ast->child[5],
				CASE_LIST))
		return (exec_case_list(ast->child[5], word, &pattern_found));
	return (EXIT_SUCCESS);
}
