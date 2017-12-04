#include "libft.h"
#include "environ.h"
#include "hash_table.h"
#include "builtin.h"
#include "t_env.h"
#include "read.h"

#include "local.h"
#include "line_editing.h"
#include "history.h"
#include "exec.h"
#include "failure.h"

static char	**split_values(char *line, t_read options)
{
	char	**values;
	char	*word;
	char	*ifs;

	values = (char **)ft_parrnew();
	word = ft_strnew(1);
	if (!(ifs = var_get_value(singleton_env(), "IFS")))
		ifs = IFS_DEFAULT;
	while (*line)
	{
		while (*line && ft_strchr(ifs, *line))
			line++;
		if (*line == '\\' && *(line + 1) && !(options.flags & R))
			read_backslash(&line, &word, 1);
		else
			ft_strpush(&word, *line++);
		if (*line && ft_strchr(ifs, *line))
		{
			ft_parrpush((void***)&values, word);
			word = ft_strnew(1);
		}
	}
	!*word ? free(word) : ft_parrpush((void***)&values, word);
	return (values);
}

static void	assign_values(char **vars, char **values, t_env *env, char *tmp)
{
	unsigned char	path;
	char			ptr;
	size_t			index;

	while (*vars)
	{
		tmp = ft_strdup(*vars);
		ptr = (env_getenv((const char**)env->environ, tmp, &index)) ? 1 : 0;
		path = (!ft_strcmp("PATH", tmp)) ? 1 : 0;
		tmp = ft_strjoin_free(tmp, "=", 0b10);
		tmp = (*values) ? ft_strjoin_free(tmp, *values++, 0b10) : tmp;
		while (!*(vars + 1) && *values)
		{
			tmp = ft_strjoin_free(tmp, " ", 0b10);
			tmp = ft_strjoin_free(tmp, *values++, 0b10);
		}
		ptr ? env_add_var_from_string(env, tmp, ft_strlen(tmp))
			: local_add_change_from_string(env, tmp);
		if (path)
			env_reload_tree_hash(env);
		vars++;
		free(tmp);
	}
}

static void	read_rc(t_read *options, char **values)
{
	if (isatty(options->fd))
	{
		if (options->prompt)
			ft_putstr(options->prompt);
		conf_term_rc(options, SAVETERM);
		if (options->delim != '\n')
			conf_term_rc(options, NO_ICANON);
		if ((options->flags & S))
		{
			conf_term_rc(options, NO_ECHO);
			write(2, "\e[?25h", 6);
		}
	}
	*values = read_get_rcinput(*options);
	if (isatty(options->fd) && (options->delim != '\n'
				|| (options->flags & S)))
		conf_term_rc(options, RESTORTERM);
}

static void	read_interact(t_env *env, t_read options, char **values)
{
	conf_term_non_canonical();
	load_prompt(env, singleton_line(), NULL, options.prompt
			? options.prompt : MAG"read> "RESET);
	put_prompt(singleton_line());
	*values = read_get_input(options);
	ft_putstr("\n");
	conf_term_canonical();
}

int		builtin_read(t_env *env, const char **argv)
{
	t_read		options;
	int			error;
	char		*values;
	char		**split;

	ft_bzero(&options, sizeof(t_read));
	options.delim = '\n';
	if ((error = read_parse_option(&options, &argv)))
		return (error);
	if (singleton_jc()->shell_is_interactive && isatty(options.fd))
		read_interact(env, options, &values);
	else
		read_rc(&options, &values);
	split = split_values(values, options);
	if (!read_parse_argv(argv))
		error = EXIT_FAILURE;
	assign_values((char**)argv, split, env, NULL);
	free(values);
	ft_arraydel(&split);
	ft_strdel(&options.prompt);
	return (error);
}
