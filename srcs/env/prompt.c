#include "libft.h"
#include "unistd.h"
#include "env.h"
#include "get_next_line.h"

void	put_color(char *str, char *color)
{
	ft_putstr(color);
	ft_putstr(str);
	ft_putstr(RESET);
}

size_t	get_git_status(int fd)
{
	size_t	len;
	char	*line;

	get_next_line(fd, &line);
	len = ft_strlen(line);
	put_color(line, GRN);
	singleton_env()->branch = line;
	close(fd);
	return (len);
}

size_t	print_git_status(t_env *env)
{
	pid_t	son;
	int	ret;
	int	fildes[2];
	static char	*exec[] = {"git", "status", "--porcelain", "--branch", NULL};

	if ((son = fork()))
	{
		waitpid(son, &ret, WUNTRACED);
		close(fildes[1]);
		return (get_git_status(fildes[0]));
	}
	else
	{
		pipe(fildes);
		dup2(fildes[1], 1);
		close(fildes[0]);
		execve("usr/bin/git", exec, env->environ);
	}
	return (0);
}

char	*get_current_directory(void)
{
	char	*dir;
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 0);
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


size_t	put_prompt(t_env *env)
{
	char	*current_dir;
	size_t	len;

	(void)env;
	put_color("➜  ", GRN);
	current_dir = get_current_directory();
	len = ft_strlen(current_dir);
	put_color(current_dir, BLU);
	free(current_dir);
	//len += print_git_status(env);
	put_color(" git:()", RED);
	//put_color(env->branch, GRN);
	put_color(" ✗ ", YEL);
	return (3 + len + 7 + 3);
}
