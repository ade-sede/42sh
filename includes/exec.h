#ifndef EXEC_H
# define EXEC_H
# include "token.h"
# include "pipe.h"
# include "ast.h"
# include "t_line.h"
# include "history.h"

typedef struct	s_redir
{
	int			id;
	int			(*f)(int, char*, t_list**, t_token_id);
}				t_redir;

/*
**	In file srcs/exec/exec_bin.c
*/

void			ft_exec_bin_absolute(t_env *env, const char **argv);
void			ft_exec_bin_path(t_env *env, const char **argv);
int				exec_bin_no_fork(t_env *env, const char **argv);
int				fork_exec_bin(t_env *env, const char **argv, t_lst_head *head);

/*
**	In file srcs/exec/exec_heredoc.c
*/

char			*heredoc_get_input(void);
int				heredoc(int io_number, char *target, t_list **redir_stack, \
				t_token_id id);

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

void			*get_exec_redir_func(t_ast *child_node);
int				merge_fd(int io_number, char *target, t_list **redir_stack, \
				t_token_id id);
int				file_redir(int io_number, char *target, t_list **redir_stack, \
				t_token_id id);
int				exec_redir(t_list *child_list, t_list **redir_stack);

/*
**	In file srcs/exec/exec_separator.c
*/

int				logical_or(t_ast *ast, t_lst_head *head);
int				semi_colon(t_ast *ast, t_lst_head *head);
int				logical_and(t_ast *ast, t_lst_head *head);
int				exec_pipe(t_ast *ast, t_lst_head *head);

/*
**	In file srcs/exec/exec_signals.c
*/

void			nothing(int signum);
void			no_handle_signals(void);

/*
**	In file srcs/exec/exec_simple_commands.c
*/

void			exec_simple_command(t_ast *ast, t_lst_head *head);

/*
**	In file srcs/exec/exec_tree.c
*/

int				exec_tree(t_ast *ast, t_lst_head *head);

/*
**	In file srcs/exec/main_loop.c
*/

void			lex_and_parse(char *buff);
char			*line_editing_get_input(t_line *line, t_hist *hist);
void			init_main_loop(t_line *line, t_hist *hist);
void			exec(t_env *env, const char **argv, t_lst_head *head);
void			main_loop(t_env *env);

/*
**	In file srcs/exec/redir_utils.c
*/

int				redir_open_file(char *target, t_token_id id);
void			close_dup(t_list *redir_stack);
void			push_dup(int io_number, int target_fd, int natural_fd, \
				t_list **redir_stack);
int				exec_dup(t_list *redir_stack);
#endif
