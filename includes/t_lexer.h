#ifndef T_LEXER_H
# define T_LEXER_H
# include "t_token.h"
# include <string.h>
# include "list.h"

/*
**	state_list is a list which has ssize_t* as data. Each of these 3 int holds
**	data about the state of the current operation:
**	data[_T_STATE] -> current state of the automaton
**	data[_T_START] -> where the current operation STARTED (index of the first character to include IN the token)
**	data[_T_END] -> where the operation ended (index of the last character to include IN the token)
**	Its a stack of ssize_t
**
**	state is a pointer to a node of state_list, representing its current state
**
**	line is the adress of a string. This string is malloc'ed by init_lexer(),
**	and must be freed at some point.
**
**	pos is our main offset, used to read the line char by char.
**
**	cmd_name_open is a flag, set to TRUE (1) if the next word we see can
**	potentially be a command name, or FALSE (0) if it is not possible
**	(obviously because we have already found one in the current command)
*/


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
	AR_EXP,
	DQUOTES,
	QUOTES,
	BS,
	NEWLINE,
};

typedef struct	s_lexer
{
	t_list		*state_list;
	t_list		*state;
	char		*line;
	size_t		pos;
	int			cmd_name_open;
	t_list		*reversed_list;
}				t_lexer;


int			init_lexer(t_lexer *lex, const char *line);
int			free_lexer(t_lexer *lex);
int			free_lexer_le(t_lexer *lex);
int			init_le_lexer(t_lexer *lex, const char *line);
void	remove_lexer(t_lexer *lex, t_list **token_list);
#endif
