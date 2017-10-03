/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_methods.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 05:14:20 by bmickael          #+#    #+#             */
/*   Updated: 2017/09/10 05:14:22 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_completion.h"
#include "common/properties.h"
#include "common/messages.h"

/*
** Logic return;
** input word and output word have similar lenght, completiom can be armed.
** When output len and input len differs, letters are posed.
** In this cas, if output is NULL, the solution must be followd by a space.
** In the other case, output contain something, we don't have to put space.
*/

int		get_completed_list(struct s_completion *ctx, char **word,
		char ***output)
{
	if (!ENABLE_COMPLETION)
		return (0);
	if (ctx == NULL)
	{
		return (error("get_completed_list",
		"ctx main context were never initialized", -1));
	}
	if (*word == NULL)
		return (0);
	if (output == NULL)
	{
		return (error("get_completed_list",
		"output variable is NULL", -1));
	}
	*output = NULL;
	comple_bin_match_trip_layer(ctx->tree, output, word, 0);
	return (0);
}

int		update_completion_tree(struct s_completion *ctx, char *path)
{
	if (!ENABLE_COMPLETION)
		return (0);
	if (ctx == NULL)
	{
		return (error("update_completion_tree",
		"ctx main context were never initialized", -1));
	}
	if (path == NULL)
		free_ternary_tree(&ctx->tree);
	else if (!ctx->path || !ft_strequ(ctx->path, path))
	{
		if (ctx->path)
			free(ctx->path);
		if (!(ctx->path = ft_strdup(path)))
			exit(EXIT_FAILURE);
		free_ternary_tree(&ctx->tree);
		create_ternary_tree(ctx, path);
	}
	return (0);
}
