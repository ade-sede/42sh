/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:41:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/18 15:41:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "libft.h"

typedef struct	s_env
{
	char		**environ;
	size_t	environ_size;
	t_list	*path;
	int		previous_exit;
}			t_env;

char			**env_create_environ(const char **original, size_t *new_size);
void			env_print_environ(const char **environ);
void			env_remove_var(t_env *env, const char *key);
char			*env_getenv(const char **environ, const char *key, size_t *index);
void			env_add_var(t_env *env, const char *key, const char *value);
void			env_change_value(t_env *env, const char *key, size_t key_index, const char *new_value);
void			env_load_shlvl_pwd(t_env *env);
void			env_load_base_env(t_env *env, const char **environ);
void			env_remove_var_index(t_env *env, size_t key_index);
void			env_create_path_list(char *path, t_list **first);
void			env_add_change(t_env *env, const char *key, const char *value);
int			return_failure(const char *str, const char *error_msg);
#endif 
