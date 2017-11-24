#ifndef EXEC_H
# define EXEC_H
# include "t_token.h"
# include "t_ast.h"
# include "parser.h"
# include "t_line.h"
# include "history.h"
# include "job_control.h"
# include "exec_symbol.h"
# include "modes.h"
# define BUFSIZE 128

typedef struct	s_redir
{
	int			id;
	int			(*f)(int, char*, t_list**, int);
}				t_redir;

int				expansion(char **string, t_lst_head *head);

/*
**	In file srcs/exec/exec_bin.c
*/

void			ft_exec_bin_absolute(t_env *env, const char **argv);
void			ft_exec_bin_path(t_env *env, const char **argv);
int				exec_bin_no_fork(t_env *env, const char **argv);
int				fork_exec_bin(t_env *env, const char **argv, t_lst_head *head);
int				exec_bin(t_env *env, const char **argv);

/*
**	In file srcs/exec/exec_heredoc.c
*/

/*
**	In file srcs/exec/exec_redir.c
*/

void			*get_exec_redir_func(int id);
int				merge_fd(int io_number, char *target, t_list **redir_stack, \
				int id);
int				file_redir(int io_number, char *target, t_list **redir_stack, \
				int id);
int				exec_redir(t_list *child_list, t_list **redir_stack);

/*
**	In file srcs/exec/exec_signals.c
*/

void			nothing(int signum);
void			no_handle_signals(void);

/*
**	In file srcs/exec/main_loop.c
*/

int				lex_and_parse(t_ast *ast, char *buff, t_modes *modes);
void			init_main_loop(t_line *line, t_hist *hist);
int				main_loop(t_env *env, t_modes *modes);
int				get_input(t_modes *modes, char **buff);

/*
**	In file srcs/exec/redir_utils.c
*/

int				safe_open(char *target, int mode);
int				redir_open_file(char *target, int id);
void			close_dup(t_list *redir_stack);
void			push_dup(int io_number, int target_fd, int natural_fd, \
				t_list **redir_stack);
int				exec_dup(t_list *redir_stack);

int				exec(t_ast	*ast);
int				is_token(t_ast *ast, int token_id);
int				is_symb(t_ast *ast, int symbol);

t_lst_func		*get_function(t_env *env, char *cmd_name);
int				exec_io_redirect(t_ast	*ast, t_list **redirect_list);
char			**get_cmd_name(t_ast *ast, int flag);
int				exec_function(t_ast *fct_body, char **av);
void			exec_redirect_list(t_ast *ast, t_list **redirect_list);
char			*stream_get_line(int stream);
char			*line_editing_get_line(t_line *line, t_hist *hist,
				void (*sig_handler)(void));
int				reopen(t_lexer *lex, t_parser *parser, t_modes *modes);

void			read_heredoc(t_ast *ast, char *target);
void			parse_heredoc(t_ast *ast);
int				exec_cmd_suffix(t_ast *ast, t_list **redirect_list, char ***av);
int				exec_cmd_prefix(t_ast *ast, t_list **redirect_list);
void			remove_lexer(t_lexer *lex, t_list **token_list);
void			remove_parser(t_parser *parser);
void			exec_main_loop(t_ast *ast);
int				layer_exec(t_env *env, char **av);

#endif
