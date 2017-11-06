#include "lexer.h"
#include "libft.h"

void	lex_action_default(t_lexer *lex, ssize_t **state_info)
{
	if (lex->line[lex->pos] == 0)
		return ;
	if (charcmp(lex->line, lex->pos, ' ') || \
			charcmp(lex->line, lex->pos, '	'))
		push_state(lex, WHITESPACE);
	else
		push_state(lex, WORD);
	(void)state_info;
}
