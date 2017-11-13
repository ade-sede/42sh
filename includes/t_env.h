#ifndef T_ENV_H
# define T_ENV_H
# include "sys/param.h"
# include "list.h"
# include "t_ast.h"
# include "t_ternary_tree.h"
# include "local.h"

typedef struct				s_lst_func
{
	struct s_lst_func		*next;
	char					*fname;
	t_ast					*fct_body;
}							t_lst_func;

typedef struct				s_env
{
	char					**environ;
	t_list					**hash_table;
	t_list					*alias;
	t_lst_func				*first_func;
	t_list					*local;
	t_list					*pos_param;
	long					option;
	t_ternary_tree			*tree;
	size_t					environ_size;
	int						previous_exit;
	char					*branch;
	pid_t					child_pid;
}							t_env;

int							env_free_env(t_env *env);
t_env						*singleton_env();
int							env_copy_env(t_env *new_env, t_env *old_env);
int							create_ternary_tree(t_env *env);
int				 add_pos_param(t_env *env, const char **argv, size_t index, size_t start);
#endif

