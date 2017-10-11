#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "t_line.h"
# include "env.h"
# include "termios.h"
# include "term.h"
# include "t_lexer.h"
# define KEY_ESCAPE 0x1B
# define KEY_SPACE 0x20
# define KEY_CTRL_D 4
# define KEY_UP 0x415B1B
# define KEY_DOWN 0x425B1B
# define KEY_RIGHT 0x435B1B
# define KEY_LEFT 0x445B1B
# define KEY_ENTER 0xA
# define KEY_BACKSPACE 0x7F
# define KEY_DELETE 2117294875
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

/*
**	Reads input from the user, and allows the user to edit his input before
**	sending it to the shell.
**	Life of the routine :
**
**	- Before it is called :
**		- A prompt is displayed, all the modules
**		are initialized (history, completion, struct t_line).
**
**	- Run time :
**		- Setup signal handler.
**		- Reads input from the user until enter is pressed or a
**		signal stops the loop.
**		- The keycode read from the user's input is matched
**		against the keycodes corresponding to different features of the shell.
**		- Appropriate feature is launched.
**
**	- Exit
**		- Returns the address of the line editing's internal buffer in which the
**		input has been bufferised.
**
**	A buffer is maintained inside the struct s_line. The line editing's purpose
**	is to match the user's input to the buffer's content, ie : if the cursor
**	moves on the screen, we need to change the index we use to append the next
**	input, and if the user's input is a character, we need to add it to the
**	buffer, and display it (refresh_line).
*/

extern int	abort_opening;

int		edit_del(t_line *line);
t_coor	get_prompt_visual_offset(t_line *line);
void	reopen_line_editing(t_lexer *lex, int res_lexer, int res_parser);
void	term_putstr(t_line *line);
void	edit_handle_sigint_reopen(int signum);
void	edit_set_signals_reopen(void);

size_t	get_char_mem_coor_relative(t_line *line, int x_move, int y_move);
size_t	get_char_mem_coor(t_line *line, size_t x, size_t y);
size_t	cursor_goto_buff(t_line *line, size_t dest_i, size_t start_i);
t_coor	get_char_visual_coor(t_line *line, ssize_t pos);

size_t	get_ws_col(void);
size_t	get_ws_row(void);

char	*control_d_heredoc(t_line *line);
void	edit_line_init(t_line *line, void (*sig_handler)(void));
char	*edit_get_input(void);
void	edit_set_signals_open(void);
void	edit_handle_sigwinch(int signum);
void	conf_term_in(void);
void	conf_term_canonical(void);
void	conf_term_normal(void);
void	put_termcap(char *capacity);
t_line	*singleton_line(void);

int		control_d(t_line *line);
int		edit_end(t_line *line);
int		edit_home(t_line *line);
int		edit_right(t_line *line);
int		edit_left(t_line *line);
int		edit_down(t_line *line);
int		edit_up(t_line *line);
int		edit_word_right(t_line *line);
int		edit_word_left(t_line *line);
int		edit_backspace(t_line *line);
void	edit_add(int keycode, t_line *line);
void	edit_refresh(t_line *line);
/* size_t	edit_refresh_nchar(t_line *line, size_t padding, char *str, size_t n); */
void	edit_refresh_clear(t_line *line);
void	edit_refresh_cursor(t_line *line);
void	edit_refresh_line(t_line *line);
void	edit_refresh_visu(t_line *line);

void	goto_termcap(char *capacity, int co, int li);
void	put_ntermcap(char *capacity, int n);

void	move_cursor_lastline(t_line *line);
void	move_cursor_lastline_from_first_line(t_line *line);
void	move_cursor_firstline_from_prev_pos(t_line *line);
void	move_cursor_firstline_from_lastline(t_line *line);
void	move_cursor_bufflen_from_lastline(t_line *line);
char	*edit_exit(t_line *line);

int		ft_insert_str_dest(char *str, char *dest, size_t dest_len);
int		edit_insert_str(t_line *line, char *dest, char *str);

void	realoc_line_buff(char **buff, unsigned int *size,
		unsigned int size_needed);

/*
** copy_paste func
*/

int		enter_visual_mode(t_line *line);
int		copy(t_line *line);
int		paste(t_line *line);
/*
**	In file prompt.c
*/

void	load_prompt(t_env *env, t_line *line, char *var, char *defaut);
void	put_prompt(t_line *line);

/*
** manipulation of cursor word func
*/

char	*get_start_word_cursor(t_line *line);
void	delete_word_cursor(t_line *line);
char	*get_current_word_cursor(t_line *line);
void	delete_word(char *to_replace);

#endif
