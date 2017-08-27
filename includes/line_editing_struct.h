/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing_struct.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:17:43 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:17:43 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_STRUCT_H
# define LINE_EDITING_STRUCT_H
# include "termios.h"
# include <string.h>

typedef struct	s_line
{
	unsigned int		pos;
	unsigned int		old_pos;
	unsigned int		len;
	unsigned int		size;
	unsigned int		prompt_len;
	size_t				ws_col;
	char				*buff;
	struct termios		canonical_mode;
	struct termios		normal_mode;
	int					visu_mode;
	size_t				visu_start;
	char				*copied_text;
	char				*prompt;
}				t_line;

typedef struct	s_edit_func
{
	unsigned long long	keycode;
	int					(*f)(t_line *);
}				t_edit_func;

#endif
