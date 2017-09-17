/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 17:06:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/17 17:08:10 by ade-sede         ###   ########.fr       */
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
	INPUT_END
}	t_lexer_state;

/*
**	Line is the string we are tokenizing.
**	Index represents our position on the string.
**	stack->data should contain a t_token.
*/

typedef struct		s_lexer
{
	const char		*line;
	size_t			index;
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
