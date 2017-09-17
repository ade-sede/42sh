/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 14:20:17 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/17 16:44:19 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "t_lexer.h"
# include <string.h>

/*
**	Every type of token we can find accoring to the POSIX STANDARD should be
**	listed in the following enums. The first enum of each groups starts at the
**	last group's last element index + 1. As if they were all defined in one
**	enum.  This will be usefull when matching them with the strings/index pair
**	of a global variable.
*/

/*
**	Words and assignement words. According to this enum, operator will have an
**	id such that `5 <= id < 20', and reserved words will have an id such as `id
**	>= 20'.
*/

typedef enum
{
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_NAME,
	TK_NEWLINE,
	TK_IO_NUMBER,
	TK_LESS = 5,
	TK_HERE,
	TK_GREAT,
	TK_SEMI,
	TK_PIPE,
	TK_AND,
	TK_AND_IF,
	TK_OR_IF,
	TK_DSEMI,
	TK_DLESS,
	TK_DGREAT,
	TK_LESSAND,
	TK_GREATAND,
	TK_LESSGREAT,
	TK_DLESSDASH,
	TK_CLOBBER,
	If = 20,
	Then,
	Else,
	Elif,
	Fi,
	Do,
	Done,
	Case,
	Esac,
	While,
	Until,
	For,
	Lbrace,
	Rbrace,
	Bang,
	In
}	t_token_id;

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
