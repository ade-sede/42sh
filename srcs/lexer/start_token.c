#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Initialize the token_start index on the right character and returns the new
**	lexer state depending on the current one
*/

int		start_token(t_lexer *lex, size_t *token_start)
{
	if (!IS_QUOTED(lex->state))
		while (lex->line[lex->index] && IS_WHITESPACE(lex->line[lex->index]))
			lex->index++;
	*token_start = lex->index;
	if (IS_QUOTED(lex->line[lex->index]))
	{
		if (IS_QUOTED(lex->state))
		{
			if(lex->state == (unsigned char)lex->line[lex->index])
			{
				lex->index++;
				return (DEFAULT);
			}
		}
		else
			return (lex->line[lex->index++]);
	}
	else if (IS_OPERATOR(lex->line[lex->index]))
	{
		lex->index++;
		return (OPERATOR);
	}
	else if (IS_WORD(lex->line[lex->index]))
		return (WORD);
	return (DEFAULT);
}
