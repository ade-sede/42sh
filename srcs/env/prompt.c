/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:20:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/24 20:51:07 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"
#include "env.h"
#include "sys/wait.h"
#include "get_next_line.h"
#include "line_editing.h"

void	put_prompt(t_line *line)
{
	ft_putstr(line->prompt);
}
char	*read_git_status(int fd)
{
        char    *line;
        char    *branch;
        char    *git_status;

        line = NULL;
        get_next_line(fd, &line);
	if (!line)
	{
		close(fd);
		return (ft_strnew(1));
	}
        if (ft_strchr(line, '/'))
                branch = ft_strdup(ft_strrchr(line, '/') + 1);
        else
                branch = ft_strdup(line + 3);
        git_status = ft_strjoin3_free(" \x1b[38;5;47mgit:(\x1b[38;5;203m", branch, "\x1b[38;5;47m)", 0);
        ft_strdel(&line);
        ft_strdel(&branch);
        if (!get_next_line(fd, &line))
                git_status = ft_strjoin_free(git_status, "\x1b[38;5;83m ✓ \x1B[0m", 4);
        else
                git_status = ft_strjoin_free(git_status, "\x1b[38;5;11m ✗ \x1B[0m", 4);
        close(fd);
        return (git_status);
}

char	*get_git_status(void)
{
        static char     *exec[] = {"git", "status", "--porcelain", "--branch", NULL};
        int     fildes[2];
        pid_t   son;
        int     ret;

        pipe(fildes);
        if ((son = fork()))
        {
                waitpid(son, &ret, WUNTRACED);
               	if (WEXITSTATUS(ret))
			return (ft_strnew(1));
                close(fildes[1]);
                return (read_git_status(fildes[0]));
        }
        else
        {
                dup2(fildes[1], 1);
                dup2(fildes[1], 2);
                close(fildes[0]);
                execve("/usr/bin/git", exec, singleton_env()->environ);
        }
	return ("NE VA JAMAIS ICI");
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

char	*get_ps1(t_env *env)
{
	char *git_status;
	char *current_dir;
	char *previous_exit;

	previous_exit = (env->previous_exit == 0) ? ft_strjoin3_free(GRN, "➜  ",RESET, 0) : ft_strjoin3_free(RED, "➜  ",RESET, 0);
	current_dir = ft_strjoin3_free(BLU, get_current_directory(), RESET, 2);
	git_status = get_git_status();
	return (ft_strjoin3_free(previous_exit, current_dir, git_status, 3));
}

void	load_prompt(t_env *env, t_line *line, char *var, char *defaut)
{
	char	*prompt;

	prompt = NULL;
	if (ft_strequ(var, "PS1"))
		prompt = get_ps1(env);
	else
		prompt = env_getenv((const char**)env->environ, var, NULL);
	if (!prompt)
		prompt = defaut;
	line->prompt_len = ft_strlen(prompt);
	line->prompt = prompt;
}
