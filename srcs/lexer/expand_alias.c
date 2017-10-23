#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "exec.h"
#include "builtin.h"

int		lexer_insert_str_dest(char *dest, char *str, size_t dest_len)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memmove((void*)(dest + len), (void*)(dest), dest_len);
	ft_strncpy(dest, str, len);
	return (1);
}

int		lexer_insert_str(t_lexer *lex, char *dest, char *str)
{
	size_t	len;
	size_t	dest_pos;
	size_t	dest_len;
	char	*tmp;

	dest_pos = dest - lex->line;
	dest_len = ft_strlen(dest);
	len = ft_strlen(str);
	tmp = ft_strnew(ft_strlen(lex->line) + len);
	ft_strcpy(tmp, lex->line);
	free((char *)lex->line);
	lex->line = tmp;
	ft_insert_str_dest((char *)lex->line + dest_pos, str, dest_len);
	return (1);
}

void	lexer_delete_word(char *to_replace)
{
	char	*end;

	end = ft_strchr(to_replace, ' ');
	if (end)
	{
		ft_memmove(to_replace, end, ft_strlen(end));
		ft_strclr(to_replace + ft_strlen(end));
	}
	else
		ft_strclr(to_replace);
}

int		check_alias(t_lexer *lex, t_token *token)
{
	t_list	*alias;

	alias = NULL;
	if (token->cmd_name)
	{
		alias = find_alias(singleton_env()->alias, token->value, \
				ft_strlen(token->value));
		if (!alias)
			return (0);
		lexer_insert_str(lex, (char *)(lex->line + lex->index), \
				ft_strchr(alias->data, '=') + 1);
		free_token(token);
		lex->cmd_name_open = 0;
		return (1);
	}
	return (0);
}
