/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing_struct.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_STRUCT_H
# define LINE_EDITING_STRUCT_H
# include "termios.h"
# include <string.h>

typedef struct	s_line
{
	unsigned int		pos;
	unsigned int		len;
	unsigned int		size;
	unsigned int		prompt_len;
	size_t				ws_col;
	char				*buff;
	struct termios		canonical_mode;
	struct termios		normal_mode;
	int					visu_mode;
	int					completion;
	int					history;
	int					btsearch;
	size_t				visu_start;
	char				*copied_text;
	char				*prompt;
	unsigned int		old_pos;
	int					heredoc;
}				t_line;

typedef struct	s_edit_func
{
	unsigned long long	keycode;
	int					(*f)(t_line *);
}				t_edit_func;

#endif
