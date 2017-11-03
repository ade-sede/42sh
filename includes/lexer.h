
#ifndef LEXER_H
# define LEXER_H
# include "t_lexer.h"
# include "t_token.h"

/*
**	ASSOCIATED DIRECTORY : lexer
*/

/*
**	In get_token_list.c
*/

int		get_token_list(t_lexer *lex, t_list **token_list, t_list *aliast_list);
#endif
