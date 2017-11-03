#ifndef LEXER_H
# define LEXER_H
# include "t_lexer.h"
# include "t_token.h"

/*
**	The following enum concerns the different states the automata can go
**	through.
*/

enum
{
	DEFAULT,
	WORD,
	WHITESPACE,
	COMMENT,
	OPERATOR,
	PARAM_EXP,
	CMD_SUBST,
	TILD_EXP,
	AR_EXP,
	DQUOTES,
	QUOTES,
	BS,
	HIST_EXP
};

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
**	In get_token_list.c
*/

int		get_token_list(t_lexer *lex, t_list **token_list, t_list *aliast_list);

/*
**	In utils.c
*/

int		change_state(t_lexer *lex, ssize_t new_state);
int		pop_state(t_lexer *lex, ssize_t	**new_info);
int		push_state(t_lexer *lex, ssize_t new_state);
ssize_t	*create_state_info(void);

/*
**	REFERENCING ACTIONS
*/


#endif
