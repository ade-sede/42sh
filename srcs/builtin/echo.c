/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

static const char	**parse_options(const char **argv, short int *n_flag, \
		short int *e_flag)
{
	char	*option_array[5];

	option_array[0] = "-n";
	option_array[1] = "-e";
	option_array[2] = "-ne";
	option_array[3] = "-en";
	option_array[4] = NULL;
	while (ft_arraychr((const char**)option_array, (const char*)*argv))
	{
		if (ft_strequ(*argv, "-n"))
			*n_flag = TRUE;
		if (ft_strequ(*argv, "-e"))
			*e_flag = TRUE;
		if (ft_strequ(*argv, "-ne") || ft_strequ(*argv, "-en"))
		{
			*e_flag = TRUE;
			*n_flag = TRUE;
		}
		argv++;
	}
	return (argv);
}

static void			print_unicode(const char *argv, size_t *i)
{
	size_t	n;
	size_t	start;
	size_t	end;
	char	*unicode_char;
	char	*tmp;

	n = 4;
	start = *i;
	end = *i;
	while (n && ft_is_hex(argv[end]))
	{
		n--;
		end++;
	}
	tmp = ft_strsub(argv, start, end - start);
	unicode_char = ft_buff_wchar((wchar_t)ft_atoi_base(tmp, 16));
	ft_putstr(unicode_char);
	free(unicode_char);
	free(tmp);
	*i = end - 1;
}

static void			print_arg(const char *argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (charcmp(argv, i, '\\'))
		{
			i++;
			if (argv[i] == 'n')
				ft_putchar('\n');
			if (argv[i] == 't')
				ft_putchar('\t');
			if (argv[i] == 'v')
				ft_putchar('\v');
			if (argv[i] == 'u')
			{
				i++;
				print_unicode(argv, &i);
			}
		}
		else
			ft_putchar(argv[i]);
		i++;
	}
}

int					builtin_echo(t_env *env, const char **argv)
{
	short int	n_flag;
	short int	e_flag;
	const char	**tmp;

	(void)env;
	n_flag = FALSE;
	e_flag = FALSE;
	argv = parse_options(argv + 1, &n_flag, &e_flag);
	tmp = argv;
	while (*argv)
	{
		if (!e_flag)
			ft_putstr(*argv);
		else
			print_arg(*argv);
		if (*(argv + 1))
			ft_putchar(32);
		argv++;
	}
	if (!n_flag)
		ft_putchar('\n');
	else if (n_flag && *tmp)
		ft_putendl("\033[30m\033[47m%\x1b[0m");
	return (EXIT_SUCCESS);
}
