#include "t_lexer.h"
#include "t_token.h"
#include "lexer.h"
#include "libft.h" 
/* static size_t	escaped_size(char *input) */ /* { */
/* 	size_t	i; */
/* 	size_t	size; */

/* 	i = 0; */
/* 	size = 0; */
/* 	while (input[i]) */
/* 	{ */
/* 		++size; */
/* 		if (input[i] == '\n' && !charcmp(input, i, '\n')) */
/* 			size -= 2; */
/* 		++i; */
/* 	} */
/* 	return (size); */
/* } */

/* char			*trim_escaped_newline(char *new_line) */
/* { */
/* 	size_t	i; */
/* 	size_t	j; */
/* 	size_t	size; */
/* 	char	*ret; */

/* 	i = 0; */
/* 	j = 0; */
/* 	size = escaped_size(new_line); */
/* 	ret = ft_memalloc(sizeof(char*) * size + 1); */
/* 	while (new_line[i]) */
/* 	{ */
/* 		if (charcmp(new_line, i, '\\') && new_line[i + 1] == '\n') */
/* 			i += 2; */
/* 		else */
/* 		{ */
/* 			ret[j] = new_line[i]; */
/* 			++j; */
/* 			++i; */
/* 		} */
/* 	} */
/* 	return (ret); */
/* } */


/*
**	Receives the address of an already existing lexer (already has an address)
**	and fills it with default values + a dup of line ( must be freed at some
**	point).
*/

int		init_lexer(t_lexer *lex, const char *line)
{
	ft_memset(lex, 0, sizeof(t_lexer));
	lex->line = ft_strdup(line);
	lex->pos = 0;
	lex->state = NULL;
	lex->state_list = NULL;
	lex->cmd_name_open = 1;
	lex->reversed_list = NULL;
	push_state(lex, DEFAULT);
	return (1);
}
