#ifndef T_TOKEN_H
# define T_TOKEN_H

# include "t_lexer.h"
# include <string.h>


/*
**	Each delimited token will have its informations contained in this token.
**	Value is the string of the delimited token.
**	Id will be assumed to be TK_WORD unless it is possible to apply another id.
**	Type corresponds to the state of the lexer when the token was delimited.
**	Size is the lenght of the string.
**	Cmd_name is a flag telling us if the token is considered to be the cmd_name
**	of a simple command.
**	Delimtier is the character that caused the token to be delimited.
*/

typedef struct		s_token
{
	char			*value;
	t_token_id		id;
	int				type;
	size_t			size;
	int				cmd_name;
	char			delimiter;
}					t_token;

/*
**	Macros to check if the id corresponds to a redirection, or a separator.
*/

# define TK_IS_REOPEN_SEP(id) (id == TK_AND_IF||id == TK_OR_IF||id == TK_PIPE)
# define TK_IS_SEP(id) (id >= TK_SEMI && id <= TK_DSEMI)
# define TK_IS_GREAT_LESS(id) ( id == TK_GREAT || id == TK_LESS )
# define TK_RP1(id) id == TK_IO_NUMBER || TK_IS_GREAT_LESS(id) || id == TK_HERE
# define TK_IS_REDIR(id) (TK_RP1(id) || (id >= TK_DLESS && id <= TK_CLOBBER))

/*
**	In file srcs/lexer/t_token.c
*/

t_token				*create_token(char *value, int type, char delimiter);
void				free_token(void *value);
void				free_token_list(t_list *token_list);
#endif
