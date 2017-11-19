#include "syntax_coloring.h"
#include "libft.h"

/*
**	The loop delimiting each token
*/

int	loop_le_delim(t_lexer *lex, t_line *line)
{
	/* while line isnt over keep delimiting */
	while (lex->pos < ft_strlen(lex->line) && lex->line[lex->pos] && delim(lex, line))
		;
	return (((int*)lex->state->data)[_T_STATE]);
}
