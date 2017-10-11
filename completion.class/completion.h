/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 05:13:29 by bmickael          #+#    #+#             */
/*   Updated: 2017/09/10 05:13:32 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

struct s_completion;

/*
** Init the completion ternary tree system.
*/

int		init_completion(struct s_completion **ctx);

/*
** Return the complete completion list for a defined part of word.
*/

int		get_completed_list(struct s_completion *ctx, char **word,
		char ***output);

/*
** Update completion tree.
*/

int		update_completion_tree(struct s_completion *ctx, char *path);

/*
** Close the completion ternary tree system.
*/

int		close_completion(struct s_completion **ctx);

#endif
