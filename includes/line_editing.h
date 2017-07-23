/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:21:43 by vcombey           #+#    #+#             */
/*   Updated: 2017/07/23 18:47:43 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "env.h"
# include "termios.h"
# include "term.h"
# define KEY_ESCAPE 0x1B
# define KEY_SPACE 0x20
# define KEY_UP 0x415B1B
# define KEY_DOWN 0x425B1B
# define KEY_RIGHT 0x435B1B
# define KEY_LEFT 0x445B1B
# define KEY_ENTER 0xA
# define KEY_BACKSPACE 0x7F
# define KEY_DELETE 0x7E335B1B
# define KEY_HOME 4741915
# define KEY_END 4610843 
# define KEY_TAB 9
# define KEY_SHIFT_UP 71683997260571
# define KEY_SHIFT_DOWN 72783508888347
# define KEY_ALT_DOWN 1113266971
# define KEY_ALT_UP 1096489755
# define KEY_ALT_RIGHT 1130044187
# define KEY_ALT_LEFT 1146821403
# define KEY_ALT_C 42947
# define KEY_ALT_P 32975
# define KEY_ALT_V 10127586
# define KEY_ALT_R 44738
# define BUFF_LINE_SIZE 10

typedef struct			s_line
{
	unsigned int		pos;
	unsigned int		old_pos;
	unsigned int		len;
	unsigned int		size;
	unsigned int		prompt_len;
	size_t			ws_col;
	char			*buff;
	struct termios		*old_term;
	int			visu_mode;
	size_t			visu_start;
	char			*copied_text;
	size_t			(*put_prompt)(t_env*);
}				t_line;

typedef struct		s_edit_func
{
	unsigned long long	keycode;
	int			(*f)(t_line *);
}			t_edit_func;

size_t				get_ws_col(void);

void	edit_line_init(t_line *line);
char	*edit_get_input(t_env *env);
void	edit_set_signals(void);
void	conf_term_in(void);
void	conf_term_out(void);
void	put_termcap(char *capacity);
t_line	*singleton_line(void);

int	edit_end(t_line *line);
int	edit_home(t_line *line);
int	edit_right(t_line *line);
int	edit_left(t_line *line);
int	edit_down(t_line *line);
int	edit_up(t_line *line);
int	edit_word_right(t_line *line);
int	edit_word_left(t_line *line);
int	edit_backspace(t_line *line);
void	edit_add(int keycode, t_line *line);
void	edit_refresh(t_line *line);
void	edit_refresh_clear(t_line *line);
void	edit_refresh_cursor(t_line *line);
void	edit_refresh_line(t_line *line);

size_t	put_prompt(t_env *env);

void	goto_termcap(char *capacity, int co, int li);
void	put_ntermcap(char *capacity, int n);

void	move_cursor_lastline(t_line *line);
void	move_cursor_firstline_from_lastline(t_line *line);
void	move_cursor_bufflen_from_lastline(t_line *line);
char	*edit_exit(t_line *line);

int	ft_insert_str_dest(char *str, char *dest, size_t dest_len);
int	edit_insert_str(t_line *line, char *dest, char *str);

void	realoc_line_buff(char **buff, unsigned int *size, unsigned int size_needed);
/*
** copy_paste func
*/

int	enter_visual_mode(t_line *line);
int	copy(t_line *line);
int	paste(t_line *line);

/*
** manipulation of cursor word func
*/

char	*get_start_word_cursor(t_line *line);
void	delete_word_cursor(t_line *line);
char	*get_current_word_cursor(t_line *line);
void	delete_word(char *to_replace);

# endif
