#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"
#include "completion.h"
#include "get_next_line.h"

#include "color.h"
#include <stdio.h>

int	file_script(char **av, t_env *env)
{
	char	*buff;
	int		fd;
	t_lexer	lex;
	t_lst_head	*head = NULL;
	t_ast	*ast;
	t_list	*token_list;
	extern	const char **environ;

	env_load_base_env(env, environ);
	history_load(singleton_hist(), env);
	fd = open(av[1], O_RDONLY);
	lex.reopen = 0;
	while (get_next_line(fd, &buff))
	{
		dprintf(2, "Line = "MAG"#"CYN"%s"MAG"#\n"RESET, buff);
		buff = ft_strchange(buff, ft_strjoin(buff, "\n"));
		lex = init_lexer(buff);
		token_list = start_lex(&lex);
		ast = NULL;
		ast = ast_parse(ast, &token_list, &head);
		exec_tree(ast, head);
		if (token_list)
			ft_simple_lst_remove(&token_list, free_token);
		ast = flush_tree(ast);
		if (head != NULL)
			ft_remove_head(&head, free_pipe);
		free(buff);
	}
	sleep(120);
	return (1);
}

int	main(int ac, char *av[])
{
	extern const char	**environ;
	t_env	*env;

	(void)ac;
	env = singleton_env();
	if (ac == 2)
		return (file_script(av, env));
#ifdef PID
	dprintf(2, BLU"%d\n"RESET, getpid());
#endif
	env_load_base_env(env, environ);
#ifndef NO_TERMCAPS
	create_ternary_tree(env);
	history_load(singleton_hist(), env);
	conf_term_in();
#endif
	main_loop(env);
	env_free_env(env);
	return (0);
}
