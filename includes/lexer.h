/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 15:26:55 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/29 13:29:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
#include "parser.h"
# include <stdio.h>

/*
**	We define macros to easily check wich type the character belongs to.
*/

# ifndef IS_QUOTED
#  define IS_QUOTED(state)	(state == 39 || state == 34)
# endif
# ifndef IS_OPERATOR
#  define __L_IS_OP1(c) (c == '<' || c == '>' || c == ';')
#  define __L_IS_OP2(c) (c == '&' || c == '|')
#  define IS_OPERATOR(c) (__L_IS_OP1(c) || __L_IS_OP2(c))
# endif
# ifndef IS_EXPAND
#  define IS_EXPAND(c) (c == '$' || c == '`')
# endif
# ifndef IS_INPUT_END
#  define IS_INPUT_END(c) (c == 0)
# endif

/*
**	Token delimitation is done according to the POSIX STANDARD found here:
**	http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
*/

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
**	>= 20'. From this, 2 easy macros :
*/

typedef enum
{
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_NAME,
	TK_NEWLINE,
	TK_IO_NUMBER,
	TK_LESS = 5,
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
**	The lexer state indicates in wich context line[pos] is.
**	Is it surrounded by dquotes ?
**	Is it surrounded by quotes ?
**	Is it after a backslash ?
**	[...]
*/

typedef enum
{
	DEFAULT,
	WORD,
	DQUOTED = 34,
	QUOTED = 39,
	BACKSLASH = 92,
	OPERATOR,
	EXPAND,
	INPUT_END
}	t_lexer_state;

typedef t_lexer_state	t_token_type;

typedef struct		s_token
{
	char			*value;
	t_token_id		id;
	t_token_type	type;
	size_t			size;
}					t_token;

/*
**	Line is the string we are tokenizing.
**	Index represents our position on the string.
**	stack->data should contain a t_token.
**	Stack is pointing on the "top" of the stack, the last token we added.
*/

typedef struct		s_lexer
{
	const char		*line;
	size_t			index;
	t_list			*stack;
	t_lexer_state	state;
}					t_lexer;

/*
**	FUNCTION DEFINITIONS
*/

/*
**	In file lexer.c
*/

t_ast				*start_lex(t_lexer *lex);
int					tokenize(t_lexer *lex, size_t token_start, \
		size_t token_end);
int					start_token(t_lexer *lex, size_t *token_start);

/*
**	in file check_match.c
*/

int					token_match(t_lexer *lex, size_t token_start);

/*
**	In file init.c
*/

t_token				*create_token(char *value, t_token_type type);
t_lexer				init_lexer(const char *line);

/*
**	In file get_token_id.c
*/

t_token_id			lex_get_token_id(t_token *token, char delimiter);

/*
**	in file match_operator.c
*/

int					match_operator(const char *value, \
		size_t token_start, size_t token_end);
t_token_id			lex_id_operator(const char *value);

/*
**	In file match_word.c
*/

int					match_word(t_lexer *lex);
int					lex_id_io_number(t_token *token, \
		char delimiter, t_token_id *id);
int					lex_id_reserved_words(t_token *token, t_token_id *id);
int					lex_id_word(t_token *token, t_token_id *id);

/*
**	In file update_state.c
*/

int					update_state(t_lexer *lex);

/*
**	In file match_expand.c
*/

int					match_expand(t_lexer *lex, size_t token_start);
#endif
