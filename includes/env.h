#ifndef ENV_H
# define ENV_H
# include "libft.h"
# include "sys/param.h"
# ifndef RED
#  define RED "\x1B[1;31m"
# endif
# ifndef GRN
#  define GRN "\x1B[1;32m"
# endif
# ifndef YEL
#  define YEL "\x1B[1;33m"
# endif
# ifndef BLU
#  define BLU "\x1B[1;34m"
# endif
# ifndef MAG
#  define MAG "\x1B[35m"
# endif
# ifndef CYN
#  define CYN "\x1B[36m"
# endif
# ifndef WHT
#  define WHT "\x1B[37m"
# endif
# ifndef RESET
#  define RESET "\x1B[0m"
# endif

typedef struct				s_ternary_tree
{
	char					c;
	char					*match;
	struct s_ternary_tree	*left;
	struct s_ternary_tree	*right;
	struct s_ternary_tree	*down;
}							t_ternary_tree;

typedef struct				s_env
{
	char					**environ;
	t_list					**hash_table;
	t_list					*alias;
	t_list					*local;
	t_list					*pos_par;
	long					option;
	t_ternary_tree			*tree;
	size_t					environ_size;
	int						previous_exit;
	char					*branch;
	pid_t					child_pid;
}							t_env;

void						free_ternary_tree(t_ternary_tree *node);
void						test_ternary_tree();
void						ternary_tree_add(t_ternary_tree *node,
		char *cur, char *str);
t_ternary_tree				*ternary_tree_new_down(char *str, char *cur);
t_ternary_tree				*ternary_tree_new(char c);
void						ternary_tree_print(t_ternary_tree *node);
int							create_ternary_tree(t_env *env);

/*
**	In file environ.c
*/

char						**env_create_environ(const char **original,
		size_t *new_size);
void						env_print_environ(const char **environ);
char						*env_getenv(const char **environ,
		const char *key, size_t *index);

/*
**	In file load_base_env.c
*/

void						env_load_shlvl_pwd(t_env *env);
void						env_load_base_env(t_env *env, const char **environ);

/*
**	In file add_var.c
*/

void						env_change_value(t_env *env, const char *key,
		size_t key_index, const char *new_value);
void						env_add_var(t_env *env, const char *key,
		const char *value);
void						env_add_change(t_env *env, const char *key,
		const char *value);
void						env_add_var_from_string(t_env *env,
		char *key_value, ssize_t eq_index);
void						env_reload_tree_hash(t_env *env);

/*
** 	In file remove_var.c
*/

void						env_remove_var_index(t_env *env, size_t key_index);
void						env_remove_var(t_env *env, const char *key);

/*
**	In file t_env.c
*/

char						*get_ps1(t_env *env, size_t *len);
int							env_free_env(t_env *env);
/*
**	In file t_env.c
*/

int							env_free_env(t_env *env);
t_env						*singleton_env();
int							env_copy_env(t_env *new_env, t_env *old_env);

/*
**	In file ft_arraydup_env_local.c
*/

char						**ft_arraydup_env_local(const char **original,
		t_list **local);
#endif
