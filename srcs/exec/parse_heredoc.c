/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"
#include "t_line.h"
#include "exec_symbol.h"

/*
**	io_here          : DLESS     here_end
**	                **| DLESSDASH here_end
**	                **;
**	here_end         : WORD
*/

static char		*expand_target(char *target)
{
	char	*ptr;
	char	*word;
	int		quote;

	quote = 0;
	ptr = ft_strnew(1);
	while (*target == ' ' || *target == '\t')
		target++;
	while (*target)
	{
		word = ft_strnew(1);
		while (*target && ((*target != ' ' && *target != '\t') || quote))
			if ((*target == '\t' || *target == '"' || *target == '\'')
				&& !quote)
				quote = *target++;
			else if (*target == quote)
				quote -= *target++;
			else
				ft_strpush(&word, *target++);
		ft_strspush(&ptr, word);
		ft_strdel(&word);
		while (*target == ' ' || *target == '\t')
			target++;
	}
	return (ptr);
}

void			read_heredoc(t_ast *ast, char *ptr)
{
	char	*buff;
	char	*ret;
	char	*target;
	char	**expanded_word;

	target = expand_target(ptr);
	ft_strpush(&target, '\n');
	ret = ft_strnew(1);
	singleton_line()->heredoc = 1;
	load_prompt(singleton_env(), singleton_line(), "heredoc", "heredoc> ");
	while (42)
	{
		buff = line_editing_get_line(singleton_line(), \
					singleton_hist(), &edit_set_signals_open);
		if (ft_strequ(buff, target) || ft_strchr(buff, 4))
			break ;
		ft_strspush(&ret, buff);
	}
	singleton_line()->heredoc = 0;
	ast->heredoc = ft_strdup(
		*(expanded_word = word_expansion(ret, 0b10)));
	ft_strdel(&target);
	ft_strdel(&ret);
	ft_arraydel(&expanded_word);
}

void			parse_heredoc(t_ast *ast)
{
	int		i;

	i = 0;
	if (!ast)
		return ;
	while (ast->child[i] && i < 7)
	{
		parse_heredoc(ast->child[i]);
		if (is_symb(ast, IO_HERE))
		{
			read_heredoc(ast, ast->child[1]->child[0]->token->value);
			return ;
		}
		i++;
	}
}
