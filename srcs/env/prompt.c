/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:20:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/08/14 14:19:40 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"
#include "env.h"
#include "sys/wait.h"
#include "get_next_line.h"
#include "line_editing.h"
	#include <stdio.h>

void	put_prompt(t_line *line)
{
	ft_putstr(line->prompt);
}
char	*read_git_status(int fd, size_t *len)
{
        char    *line;
        char    *branch;
        char    *git_status;

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
        ft_strdel(&line);
	*len += ft_strlen(branch);
        git_status = ft_strjoin3_free(" \x1b[38;5;47mgit:(\x1b[38;5;203m", branch, "\x1b[38;5;47m)", 2);
	*len += 7;
        if (get_next_line(fd, &line))
                git_status = ft_strjoin_free(git_status, "\x1b[38;5;83m ✓ \x1B[0m", 2);
        else
                git_status = ft_strjoin_free(git_status, "\x1b[38;5;11m ✗ \x1B[0m", 2);
	*len += 3;
        ft_strdel(&line);
	while (get_next_line(fd, &line))
		free(line);
        return (git_status);
}

char	*get_git_status(size_t *len)
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
		{
			*len = *len + 1;
			return (ft_strdup(" "));
		}
                close(fildes[1]);
                return (read_git_status(fildes[0], len));
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

char	*get_ps1(t_env *env, size_t *len)
{
	char *git_status;
	char *current_dir;
	char *previous_exit;

	previous_exit = (env->previous_exit == 0) ? ft_strjoin3_free(GRN, "➜  ",RESET, 0) : ft_strjoin3_free(RED, "➜  ",RESET, 0);
	*len += 3;
	current_dir = get_current_directory();
	*len += ft_strlen(current_dir);
	current_dir = ft_strjoin3_free(CYN, current_dir, RESET, 2);
	git_status = get_git_status(len);
	return (ft_strjoin3_free(previous_exit, current_dir, git_status, 7));
}

void	load_prompt(t_env *env, t_line *line, char *var, char *defaut)
{
	char	*prompt;
	size_t	len;

	len = 0;
	prompt = NULL;
	if (ft_strequ(var, "PS1"))
		prompt = get_ps1(env, &len);
	else
		prompt = env_getenv((const char**)env->environ, var, NULL);
	if (!prompt)
		prompt = defaut;
	if (ft_strequ(var, "PS1"))
		line->prompt_len = len;
	else
		line->prompt_len = ft_strlen(prompt);
	if (line->prompt)
		free(line->prompt);
	line->prompt = prompt;
}
