/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:42:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:42:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LEXER_H
# define T_LEXER_H
# include <string.h>
# include "list.h"

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
	NEWLINE,
	INPUT_END
}	t_lexer_state;

/*
**	Line is the string we are tokenizing.
**	Index represents our position on the string.
**	stack->data should contain a t_token.
*/

typedef struct		s_lexer
{
	char			*line;
	size_t			index;
	size_t			token_start;
	t_list			*stack;
	int				reopen;
	t_lexer_state	state;
	int				last_id;
	int				cmd_name_open;
}					t_lexer;

/*
**	In file srcs/lexer/t_lexer.c
*/

t_lexer				init_lexer(const char *line);
#endif
