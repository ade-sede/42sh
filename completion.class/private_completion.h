/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_completion.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 05:14:38 by bmickael          #+#    #+#             */
/*   Updated: 2017/09/10 05:14:42 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_COMPLETION_H
# define PRIVATE_COMPLETION_H

# include <stdlib.h>
# include <dirent.h>
# include "libft.h"

# define MALLOC_UNIT 4096

typedef struct	s_ternary_tree
{
	char					c;
	char					*match;
	struct s_ternary_tree	*left;
	struct s_ternary_tree	*right;
	struct s_ternary_tree	*down;
}				t_ternary_tree;

typedef struct	s_completion
{
	t_ternary_tree			*tree;
	char					*path;
}				t_completion;

typedef struct	s_fourretout
{
	char		***matches;
	char		**cur;
	int			i;
}				t_fourretout;

/*
void			comple_bin_match_trip_tree(t_ternary_tree *node,
										char ***matches,
										char **cur,
										size_t size);
*/
void			ternary_tree_add(t_ternary_tree *node, char *cur, char *str);
t_ternary_tree	*ternary_tree_new_down(char *str, char *cur);
int				create_ternary_tree(struct s_completion *ctx, char *path);
int				free_ternary_tree(t_ternary_tree **node);

/*
void			comple_bin_match_trip_layer(t_ternary_tree *node,
				char ***matches, char **cur, size_t size);
*/

void			comple_bin_match_trip_layer(t_ternary_tree *node,
				char ***matches, char **cur, size_t size);

#endif
