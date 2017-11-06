#ifndef LEXER_H
# define LEXER_H
# include "t_lexer.h"
# include "t_token.h"
# include <string.h>
# include "list.h"

/*
**	Struct used to get action depending on state
*/

struct	s_lex_action
{
	ssize_t	state;
	void	(*func)(t_lexer *lex, ssize_t **state_info);
};

/*
**	ASSOCIATED DIRECTORY : lexer
*/

/*
**	In get_token.c
*/

t_token	*get_token(t_lexer *lex);

/*
**	In get_token_list.c
*/

int		get_token_list(t_lexer *lex, t_list **token_list, t_list *aliast_list);

/*
**	In utils.c
*/

int		change_state(t_lexer *lex, ssize_t new_state);
int		pop_state(t_lexer *lex, ssize_t	**new_info);
int		push_state(t_lexer *lex, ssize_t new_state);
int		consume_input(t_lexer *lex, ssize_t *info);
ssize_t	*create_state_info(void);

/*
**	REFERENCING ACTIONS
*/

void	lex_action_default(t_lexer *lex, ssize_t **state_info);
void	lex_action_word(t_lexer *lex, ssize_t **state_info);
void	lex_action_whitespace(t_lexer *lex, ssize_t **state_info);

#endif
