/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 15:26:55 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/01 19:18:17 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H # define LEXER_H 
/*
**	Every type of token we can find accoring to the POSIX STANDARD
*/

typedef enum
{
		WORD,
		ASSIGNMENT_WORD,
		NAME,
		NEWLINE,
		IO_NUMBER,
		AND_IF,
		OR_IF,
		DSEMI,
		DLESS,
		DGREAT,
		LESSAND,
		GREATAND,
		LESSGREAT,
		DLESSDASH,
/*
**	Reserved words
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
		Bang,
		In,
}		t_token_identifier;

/*
**	The lexer state indicates in wich context line[pos] is.
**	Is it surrounded by dquotes ?
**	Is it surrounded by quotes ?
**	[...]
*/

typedef enum
{
		IN_NONE = 0,
		IN_WORD,
		IN_DQUOTES = 34,
		IN_QUOTES = 29,
		IN_OPERATOR,
		IN_PAREN,
		IN_BACKQUOTES,
		IN_BACKSLASH,
		IN_BRACES,
		IN_BRACKETS
}		t_lexer_state;

typedef enum
{
		NONE,
		S_WORD,
		S_DQUOTED,
		S_QUOTED,
		S_OPERATOR,
}		t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	t_token_identifier identifier;
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

#endif
