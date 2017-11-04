#ifndef EXEC_H
# define EXEC_H
# include "t_token.h"
# include "pipe.h"
# include "t_ast.h"
# include "parser.h"
# include "t_line.h"
# include "history.h"
# include "job_control.h"
# include "exec_symbol.h"

typedef struct	s_redir
{
	int			id;
	int			(*f)(int, char*, t_list**, t_token_id);
}				t_redir;

int			expansion(char **string, t_lst_head *head);

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

int				exec_heredoc(t_list *child_list, t_list **redir_stack);

/*
**	In file srcs/exec/exec_pipe.c
*/

int				p_right(t_pipe *pr, t_ast *ast, t_lst_head *head);
int				p_both(t_pipe *pr, t_pipe *pl, t_ast *ast, t_lst_head *head);
int				wait_zombies(t_lst_head *head);
int				p_left(t_pipe *pl, t_ast *ast, t_lst_head *head);
int				check_pipes(t_ast *ast, t_lst_head *head);

/*
**	In file srcs/exec/exec_redir.c
*/

void			*get_exec_redir_func(t_token_id id); \
int				merge_fd(int io_number, char *target, t_list **redir_stack, \
				t_token_id id);
int				file_redir(int io_number, char *target, t_list **redir_stack, \
				t_token_id id);
int				exec_redir(t_list *child_list, t_list **redir_stack);

/*
**	In file srcs/exec/exec_signals.c
*/

void			nothing(int signum);
void			no_handle_signals(void);

/*
**	In file srcs/exec/main_loop.c
*/

void			lex_and_parse(t_ast *ast, char *buff);
char			*line_editing_get_input(t_line *line, t_hist *hist,
		void (*sig_handler)(void));
void			init_main_loop(t_line *line, t_hist *hist);
void	main_loop(t_env *env, int stream, char *buff_c_opt, int c_opt);

/*
**	In file srcs/exec/redir_utils.c
*/

int				redir_open_file(char *target, t_token_id id);
void			close_dup(t_list *redir_stack);
void			push_dup(int io_number, int target_fd, int natural_fd, \
				t_list **redir_stack);
int				exec_dup(t_list *redir_stack);

int				exec(t_ast	*ast);
int				is_token(t_ast *ast, int token_id);
int				is_symb(t_ast *ast, int symbol);

void			exec_io_redirect(t_ast	*ast, t_list **redirect_list);

char	*get_cmd_name(t_ast	*ast);
t_ast	*get_function(t_env *env, char *cmd_name);
int		exec_function(t_ast *fct_body, char **av);
char	*file_get_input(int stream);
void	exec_redirect_list(t_ast *ast, t_list **redirect_list);
#endif
