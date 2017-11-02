#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H
/* A process is a single process.  */
# include <unistd.h>
# include <term.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include "t_ast.h"
# include "libft.h"

typedef struct	s_process
{
	struct s_process	*next;
	t_ast				*command;
	char				*av;
	pid_t				pid;
	char				completed;
	char				stopped;
	char				signaled;
	int					status;
}				t_process;

typedef struct	s_job
{
	struct s_job	*next;
	char			*command;
	t_process		*first_process;
	pid_t			pgid;
	char			notified;
	int				foreground;
	struct termios	tmodes;
	int				stdin;
	int				stdout;
	int				stderr;
	int				exit_status;
}				t_job;

typedef struct	s_job_control
{
	t_job	*first_job;
	pid_t	shell_pgid;
	struct	termios shell_tmodes;
	int		shell_terminal;
	int		shell_is_interactive;
}				t_job_control;


void	init_shell();
void	launch_job(t_job_control *jc, t_job *j, int foreground);
int		mark_process_status(t_job_control *jc, pid_t pid, int status);
void	do_job_notification(t_job_control *jc);
int		job_is_stopped(t_job *j);
int		job_is_completed(t_job *j);
void	put_job_in_foreground(t_job_control *jc, t_job *j, int cont, int in_a_fork);
void	put_job_in_background(t_job *j, int cont);
void	mark_job_as_running(t_job *j);
void	continue_job(t_job *j, int foreground);
t_job	*find_job(t_job_control *jc, pid_t pgid);
void	wait_for_job(t_job_control *jc, t_job *j);
void	format_job_info(t_job *j, const char *status);
t_job	*job_new();
t_process	*process_new(t_ast *command);
void	process_add(t_process *new, t_process **first_process);
t_job_control	*singleton_jc(void);
void	format_job_info_process(t_job *j, const char *status);
void	job_add(t_job *new, t_job **first_job);
void	job_pushback(t_job *new, t_job **first_job);
t_job	*get_last_job(t_job *j);
void	format_job_info_process(t_job *j, const char *status);
void	update_status(t_job_control *jc);
void	job_free(t_job *job);

#endif
