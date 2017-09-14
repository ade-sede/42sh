#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "exec.h"
#include "builtin.h"
#include <stdio.h>

/*
**	We are reading our input line 1 char a time, looking for the delimiter of
**	our token. Everytime we're done matching a token, we reset our token_start
**	wich gives us the index of the first char of the token.
**
**	If the character we are currently reading completes the match :
**	-	Create a token from what we just read.
**	-	Assign an id (type ?) to the token.
**	-	Push this token onto the stack (here adding it at the start of the
**	list).
*/

/*
**		DETERMINING WHERE A TOKEN START AND ENDS :
**
**	See POSIX STANDARDS @ Token Recognition (2.3)
**
**	The last char of the token we matched is either the one we are on, or the
**	one before depending on wether or not we were in a "contained" token.
**	Examples:			`ls .'
**						   ^
**			When we reach this space, we have a match and line[index] == ' ';
**				The token "ls" ends at the char line[index - 1];
**
**			`"This is  a quoted string"ls'
**								      ^
**			When we reach the `"' we have a match. The token ends on this char.
**
**	The index of the last char included in the token should be returned by the
**	token_match() function.
**	We always want index to be on the char following the last char of the token
**	we just closed.
*/

/*
** Token id is determined by the immedaite context of the token and the state
** of the lexer.
*/

t_list	*start_lex(t_lexer *lex)
{
	size_t	token_start;
	ssize_t	ret;
	size_t	token_end;

	token_start = 0;
	token_end = 0;
	while (lex->line && lex->line[lex->index])
	{
		lex->state = start_token(lex, &token_start);
		if (lex->state == INPUT_END)
			break ;
		while ((ret = token_match(lex, token_start)) == -1)
			lex->index++;
		token_end = (size_t)ret;
		tokenize(lex, token_start, token_end);
		lex->state = WORD;
	}
	ft_strdel((char **)&lex->line);
	return (lex->stack);
}

/*
**	Rajouter le token qu'on vient de creer a lex->stack
**	exec_expand prend la t_list lex->stack en argument. Se base sur le dernier token.
*/

int	lexer_insert_str_dest(char *dest, char *str, size_t dest_len)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memmove((void*)(dest + len), (void*)(dest), dest_len);
	ft_strncpy(dest, str, len);
	return (1);
}

int	lexer_insert_str(t_lexer *lex, char *dest, char *str)
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
		alias = find_alias(singleton_env()->alias, token->value, ft_strlen(token->value));
		if (!alias)
			return (0);
		lexer_insert_str(lex, (char *)(lex->line + lex->index), ft_strchr(alias->data, '=') + 1);
		free_token(token);
		lex->cmd_name_open = 0;
		return (1);
	}
	return (0);
}

int		tokenize(t_lexer *lex, size_t token_start, size_t token_end)
{
	char	*value;
	t_token	*token;
	t_list	*node;

	value = ft_strsub(lex->line, token_start, token_end - token_start + 1);
	token = create_token(value, lex->state, lex->line[lex->index]);
	token->id = lex_get_token_id(lex, token);
	lex->last_id = token->id;
	if (TK_IS_SEP(token->id))
		lex->cmd_name_open = 1;
#ifdef LEXER_DEBUG
		dprintf(2, "Token->value = "MAG"#"CYN"%s"MAG"#\n"RESET"Token->id = "YEL"%d\n"RESET"Token->type = "BLU"%d\n"RESET"Token->cmd_name = "PNK"%d\n"RESET, token->value, token->id, token->type, token->cmd_name);//			REMOVE		
#endif
	if (check_alias(lex, token))
		return (1);
	node = exec_expand(token);
	if (lex->stack == NULL)
		lex->stack = node;
	else
		ft_simple_lst_pushback(&(lex->stack), node);
	return (1);
}
