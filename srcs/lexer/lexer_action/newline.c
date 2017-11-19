#include "lexer.h"
#include "libft.h"

int		lex_action_newline(t_lexer *lex, struct s_info **state_info)
{
	consume_input(lex);
	pop_state(lex, state_info);
	return (TRUE);
}
