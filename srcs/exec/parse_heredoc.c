#include "libft.h"
#include "exec.h"
#include "t_line.h"
#include "exec_symbol.h"

/*
**io_here          : DLESS     here_end
**                 **| DLESSDASH here_end
**                 **;
**here_end         : WORD                      / Apply rule 3
**
*/

void	read_heredoc(t_ast *ast, char *target)
{
	char	*buff;
	char	*cat;

	target = ft_strjoin(target, "\n");
	singleton_line()->heredoc = 1;
	load_prompt(singleton_env(), singleton_line(), "heredoc", "heredoc> ");
	cat = ft_strnew(0);
	while (42)
	{
		buff = ft_strdup(line_editing_get_line(singleton_line(), \
					singleton_hist(), &edit_set_signals_open));
		if (ft_strequ(buff, target) || ft_strchr(buff, 4))
			break ;
		cat = ft_strjoin_free(cat, buff, 0b11);
	}
	singleton_line()->heredoc = 0;
	ast->heredoc = cat;
}

void	parse_heredoc(t_ast *ast)
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

