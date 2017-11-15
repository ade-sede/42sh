#ifndef T_LINE_H
# define T_LINE_H
# include "termios.h"
# include "read.h"
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
	struct termios		non_canonical_mode;
	int					visu_mode;
	int					completion;
	int					history;
	int					btsearch;
	int					verbatim;
	size_t				visu_start;
	char				*copied_text;
	char				*prompt;
	unsigned int		old_pos;
	int					heredoc;
	void				(*sig_handler)(void);
	ssize_t				col_target;
	t_read				*read;
	int					read_builtin;
}				t_line;

typedef struct	s_edit_func
{
	unsigned long long	keycode;
	int					(*f)(t_line *);
}				t_edit_func;

#endif
