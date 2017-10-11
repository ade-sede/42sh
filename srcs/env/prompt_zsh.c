#include "libft.h"
#include "unistd.h"
#include "env.h"
#include "sys/wait.h"
#include "get_next_line.h"
#include "line_editing.h"
#include "failure.h"

char	*read_git_status(int fd, size_t *len, char *git_status)
{
	char	*line;

	if (get_next_line(fd, &line))
	{
		git_status = ft_strjoin_free(git_status, "\x1b[38;5;11m ✗ \x1B[0m", 2);
		ft_strdel(&line);
	}
	else
		git_status = ft_strjoin_free(git_status, "\x1b[38;5;83m ✓ \x1B[0m", 2);
	*len += 3;
	while (get_next_line(fd, &line))
		free(line);
	return (git_status);
}

char	*read_git_branch(int fd_close, int fd, size_t *len)
{
	char	*line;
	char	*branch;
	char	*git_status;

	close(fd_close);
	line = NULL;
	get_next_line(fd, &line);
	if (!(line))
	{
		close(fd);
		return (ft_strnew(1));
	}
	if (ft_strchr(line, '/'))
		branch = ft_strdup(ft_strrchr(line, '/') + 1);
	else
		branch = ft_strdup(line + 3);
	if (ft_strchr(branch, ' '))
		*ft_strchr(branch, ' ') = 0;
	ft_strdel(&line);
	*len += ft_strlen(branch);
	git_status = ft_strjoin3_free(" \x1b[38;5;47mgit:(\x1b[38;5;203m",
			branch, "\x1b[38;5;47m)", 2);
	*len += 7;
	return (read_git_status(fd, len, git_status));
}

char	*get_git_status(size_t *len)
{
	static char	*exec[] = {"git", "status", "--porcelain", "--branch", NULL};
	int			fildes[2];
	pid_t		son;
	int			ret;

	if (pipe(fildes) != 0)
		investigate_error(NULL, "prompt", NULL, 0);
	if ((son = fork()))
	{
		waitpid(son, &ret, WUNTRACED);
		if (WEXITSTATUS(ret))
		{
			*len = *len + 1;
			return (ft_strdup(" "));
		}
		return (read_git_branch(fildes[1], fildes[0], len));
	}
	else
	{
		dup2(fildes[1], 1);
		dup2(fildes[1], 2);
		close(fildes[0]);
		execve("/usr/bin/git", exec, singleton_env()->environ);
	}
	return ("An error occured");
}

char	*get_current_directory(void)
{
	char	*dir;
	char	*buff;

	buff = NULL;
	if ((buff = getcwd(buff, 0)) == NULL)
		return ((void*)(long)investigate_error("/dev/null", "prompt", NULL, 0));
	if (ft_strequ(buff, "/"))
		return (buff);
	if ((dir = ft_strrchr(buff, '/')))
	{
		dir = ft_strdup(dir + 1);
		free(buff);
	}
	else
		dir = buff;
	return (dir);
}

char	*get_ps1(t_env *env, size_t *len)
{
	char *git_status;
	char *current_dir;
	char *previous_exit;

	previous_exit = (env->previous_exit == 0) ? \
		ft_strjoin3_free(GRN, "➜  ", RESET, 0) : \
			ft_strjoin3_free(RED, "➜  ", RESET, 0);
	*len += 3;
	if ((current_dir = get_current_directory()) == NULL)
		current_dir = ft_strnew(0);
	*len += ft_strlen(current_dir);
	current_dir = ft_strjoin3_free(CYN, current_dir, RESET, 2);
	git_status = get_git_status(len);
	return (ft_strjoin3_free(previous_exit, current_dir, git_status, 7));
}
