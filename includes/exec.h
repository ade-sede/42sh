
# ifndef EXEC_H
# define EXEC_H

/*
** In exec_bin.c
*/

int	fork_exec_bin(t_env *env, const char **argv);

/*
** In main_loop.c
*/

void	main_loop(t_env *env);

#endif
