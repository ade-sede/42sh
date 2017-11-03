#ifndef T_LEXER_H
# define T_LEXER_H
# include "t_token.h"

/*
**	State is a list which has int [3] has data. Each index of these 3 int holds data about the state of the current operation (_T_STATE -> current state of the automaton, _T_START -> where the current operation STARTED, _T_END -> 
*/

typedef struct	s_lexer
{
	t_list		*state;
}				t_lexer;
#endif
