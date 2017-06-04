/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 15:26:55 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/04 17:01:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H 
# define LEXER_H 
# include "libft.h"
# include <stdio.h>
# ifndef IS_QUOTED
#  define IS_QUOTED(state)	(state == 39 || state == 34 || state == 92)
# endif
# ifndef IS_OPERATOR
#  define IS_OPERATOR(c) (c == '<' || c == '>' || c == '|' || c == ';'\
		|| c == '&')
# endif
# ifndef IS_SURROUNDED
#  define IS_SURROUNDED(state) (state == 34 || state == 39 || state == PAREN)
# endif
# ifndef IS_INPUT_END
#  define IS_INPUT_END(c) (c == 0 || c == EOF)
# endif
# ifndef IS_WORD
#   define IS_WORD(c) (ft_isalpha(c))
# endif

/*
**	Above we define macros to easily check wich type the character belongs to.
*/

/*
**	Every type of token we can find accoring to the POSIX STANDARD
*/

typedef enum
{
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_LESS,
	TK_DLESS,
	TK_DGREAT,
	TK_GREA,
	TK_NAME,
	TK_NEWLINE,
	TK_IO_NUMBER,
	TK_AND_IF,
	TK_OR_IF,
	TK_PIPE,
	TK_AND,
	TK_SEMI,
	TK_DSEMI,
	TK_LESSAND,
	TK_GREATAND,
	TK_LESSGREAT,
	TK_DLESSDASH,
/*
**	Strings below should be used to match shell reserved words
*/
	If,
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
	Bang = '!',
	In,
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
	PAREN,
	BACKQUOTES,
	BRACES,
	BRACKETS,
	INPUT_END
}		t_lexer_state;

typedef t_lexer_state t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_id		id;
	t_token_type	type;
	size_t			size;
}				t_token;

/*
**	Line is the string we are tokenizing.
**	Index represents our position on the string.
**	stack->data should contain a t_token. 
**	Stack is pointing on the "top" of the stack, the last token we added.
*/

typedef struct	s_lexer
{
	const char			*line;
	size_t			index;
	t_list			*stack;
	t_lexer_state	state;
}				t_lexer;

/*
**	FUNCTION DEFINITIONS
*/
/*
**	In file lexer.c
*/

int		start_lex(t_lexer *lex);
int		tokenize(t_lexer *lex, size_t token_start, size_t token_end);
int		start_token(t_lexer *lex, size_t *token_start);
int		token_match(t_lexer *lex, size_t token_start);

/*
**	In file init.c
*/

t_token		*create_token(char *value, t_token_type type);
t_lexer		init_lexer(const char *line);

/*
**	In file get_token_id.c
*/

int			get_token_id(t_token *token);
#endif
