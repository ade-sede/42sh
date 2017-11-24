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

static void			backslash(char **line, char **word, char quote)
{
	(*line)++;
	if (quote && **line == 'n')
		ft_strpush(word, '\n');
	if (quote && **line == 't')
		ft_strpush(word, '\t');
	if (quote && **line == 'v') ft_strpush(word, '\v');
	if (quote && **line == 'a')
		ft_strpush(word, '\a');
	if (quote && **line == 'b')
		ft_strpush(word, '\b');
	if (quote && **line == 'f')
		ft_strpush(word, '\f');
	if (quote && **line == 'r')
		ft_strpush(word, '\r');
	else
		ft_strpush(word, **line);
	(*line)++;
}

static char			**split_values(char *line, t_read options)
{
	char			**values;
	char			*word;

	values = (char **)ft_parrnew();
	word = ft_strnew(0);
//	line[ft_strlen(line) - 1] = '\0';
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line)
	{
		if (*line == '\\' && *(line + 1) && !(options.flags & R))
			backslash(&line, &word, 1);
		else
			ft_strpush(&word, *line++);
		if (*line == ' ' || *line == '\t')
		{
			ft_parrpush((void***)&values, word);
			word = ft_strnew(0);
		}
		while (*line == ' ' || *line == '\t')
			line++;
	}
	!*word ? free(word) : ft_parrpush((void***)&values, word);
	return (values);
}

static void			assign_values(char **vars, char **values, t_env *env)
{
	char		ptr;
	size_t		index;
	size_t		 len;
	unsigned char	path;

	while (*vars)
	{
		ptr = (env_getenv((const char**)env->environ, *vars, &index)) ? 1 : 0;
		len = ft_strlen(*vars);
		path = (!ft_strcmp("PATH",*vars)) ? 1 : 0;
		ft_strpush(vars, '=');
		if (*values)
			ft_strspush(vars, *values++);
		while (!*(vars + 1) && *values)
		{
			ft_strpush(vars, ' ');
			ft_strspush(vars, *values++);
		}
		ptr ? env_add_var_from_string(env, *vars, len) : local_add_change_from_string(env, *vars);
		if (path)
			env_reload_tree_hash(env);
		vars++;
	}
}

static char			parse_option(t_read *options, const char ***args)
{
	char *option;
	while (*++*args && ***args == '-')
	{
		option = (char*)**args + 1;
		if (!(parse_read(option, options, (char***)args)))
			return (0);
	}
	return (1);
}

int					builtin_read(t_env *env, const char **argv)
{
	int		error;
	t_read	options;
	t_line	*line;
	char	*values;
	char	**split;

	(void)env;
	line = singleton_line();
	error = 0;
	options.flags = 0;
	options.fd = 0;
	options.prompt = 0;
	options.nchars = 0;
	options.delim = '\n';
	/*
	**if (!parse_option(&options, &argv))
		**return (2);
	*/
	if (!(error = parse_option(&options, &argv)) || error == 2)
		return !(error) ? 2 : 1;
	 if (singleton_jc()->shell_is_interactive && isatty(options.fd))
	 {
	 	conf_term_non_canonical();
		load_prompt(env, line, NULL,options.prompt ?options.prompt: "read> ");//"$> ");
		put_prompt(line);
		values = read_get_input(options);
		ft_putstr("\n");
	 	conf_term_canonical();
	 }
	 else
		values = read_get_rcinput(options);
	
	split = split_values(values, options);
	assign_values((char**)argv, split, env);
	free(values);
	ft_arraydel(&split);
	return (0);
}
