/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:13:37 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/18 15:03:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include "env.h"

int		replace_quotes(char *str)
{
	int		i;
	int		quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && quote == 0)
			quote = 1;
		else if (str[i] == '"' && quote == 1)
			quote = 0;
		else if (quote == 0 && (str[i] == ' '))
			str[i] = -1;
		i++;
	}
	return (quote);
}

char	**ft_char_to_av(char *str)
{
	int		quote;
	char	*buf;
	char	**av;

	quote = replace_quotes(str);
	if (quote == 1)
	{
		ft_putstr("dquote> ");
		get_next_line(0, &buf);
		str = ft_strjoin_free(str, buf, 3);
		return (ft_char_to_av(str));
	}
	else
	{
		av = ft_strsplit(str, -1);
		free(str);
		return (av);
	}
}

void	init_str(char **argv, char *str)
{
	char *end;

	if (ft_strequ(argv[1], "-n"))
		end = ft_strstr(str, "-n") + 2;
	else
		end = ft_strstr(str, "echo") + 4;
	while (str < end)
	{
		*str = -1;
		str++;
	}
}

void	putchar_echo(char **av, int *i, int *j)
{
	if (av[*i][*j] == '\\' && av[*i][*j + 1] == 'n')
	{
		ft_putchar('\n');
		*j = *j + 1;
	}
	else if (av[*i][*j] == '\\' && av[*i][*j + 1] == 't')
	{
		ft_putchar('\t');
		*j = *j + 1;
	}
	else if (av[*i][*j] == '\\' && av[*i][*j + 1] == '\\')
	{
		ft_putchar('\\');
		*j = *j + 1;
	}
	else if (av[*i][*j] != '"')
		ft_putchar(av[*i][*j]);
	*j = *j + 1;
}

void	ft_echo(char **argv, char *str)
{
	char	**av;
	int		n_flag;
	int		i;
	int		j;

	init_str(argv, str);
	n_flag = 0;
	if (ft_strequ(argv[1], "-n"))
		n_flag = 1;
	av = ft_char_to_av(str);
	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
			putchar_echo(av, &i, &j);
		if (av[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (n_flag)
		ft_putstr("\033[30m\033[47m%\x1b[0m");
	ft_putchar('\n');
	tab_free(av);
}
