/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

/*
**	Creates a token, storing the string value, its type and the value's lenght.
*/

t_token		*create_token(char *value, int type, char delimiter)
{
	t_token		*token;

	token = palloc(sizeof(*token));
	token->delimiter = delimiter;
	token->value = value;
	token->id = 0;
	token->type = type;
	token->size = ft_strlen(value);
	token->cmd_name = 0;
	return (token);
}

void		free_token(void *value)
{
	t_token *token;

	token = (t_token*)value;
	if (token->value)
		free(token->value);
	free(token);
}

void		free_token_list(t_list *token_list)
{
	t_list	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free_token(token_list->data);
		free(token_list);
		token_list = tmp;
	}
}
