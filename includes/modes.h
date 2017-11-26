/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:44 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODES_H
# define MODES_H
# include "t_token.h"
# include "t_ast.h"
# include "parser.h"
# include "t_line.h"
# include "history.h"
# include "job_control.h"
# include "exec_symbol.h"

# define INTERACTIVE_MODE 0
# define FILE_MODE 1
# define STRING_MODE 2

/*
**	the shell can be in 3 modes:
**	interactif
**	non interactif with input from stream --- non interactif
**	input form a string (-c option)		--- non interactif
*/

typedef struct	s_modes
{
	int			mode;
	int			stream;
	char		*string;
}				t_modes;

#endif
