/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word_range.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:16 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bang.h"
#include "libft.h"
#include "lexer.h"

void		parse_end(const char **source, int *start, int *end)
{
	if (**source == '-')
	{
		++(*source);
		if (**source == '$')
			*end = -1;
		else if (ft_isdigit(**source))
		{
			*end = ft_atoi_base((char*)*source, 10);
			while (ft_isdigit(**source))
				++(*source);
		}
		else
			*end = -2;
	}
	else if (**source == '*')
		*end = -1;
	else
		*end = *start;
}

static void	last_switch(const char **source, int *start, int *end)
{
	if (ft_isdigit(**source))
	{
		*start = ft_atoi_base((char*)*source, 10);
		while (ft_isdigit(**source))
			++(*source);
		parse_end(source, start, end);
	}
	else if (**source == '*')
	{
		++(*source);
		*start = 1;
		*end = -1;
	}
}

void		parse_range(const char **source, int *start, int *end)
{
	if (**source == '^')
	{
		*start = 1;
		++(*source);
		parse_end(source, start, end);
	}
	else if (**source == '-')
	{
		*start = 0;
		parse_end(source, start, end);
	}
	else if (**source == '$')
	{
		++(*source);
		*start = -1;
		*end = -1;
	}
	else
		last_switch(source, start, end);
}

static int	concat(t_list *start_node, t_list *end_node, \
		t_word *word_designator, t_list **list)
{
	while (start_node && start_node != end_node->next)
	{
		w_addstr(word_designator, ((t_token*)start_node->data)->value);
		w_addchar(word_designator, ' ');
		start_node = start_node->next;
	}
	word_designator->str[word_designator->actlen - 1] = 0;
	--word_designator->actlen;
	ft_simple_lst_remove(list, free_token);
	return (1);
}

int			extract_words(int start, int end, \
		t_word event, t_word *word_designator)
{
	t_list	*start_node;
	t_list	*end_node;
	t_list	*list;

	list = NULL;
	if (start > end && end != -1 && end != -2)
		return (TRUE);
	lex_loop(event.str, &list);
	if (start == -1)
		start_node = ft_last_simple_lst(list);
	else
		start_node = ft_simple_lst_get_n(list, start);
	if (end == -1)
		end_node = ft_last_simple_lst(list);
	else if (end == -2)
		end_node = ft_previous_last_simple_lst(list);
	else
		end_node = ft_simple_lst_get_n(list, end);
	if (!end_node || !start_node)
	{
		ft_simple_lst_remove(&list, free_token);
		return (TRUE);
	}
	concat(start_node, end_node, word_designator, &list);
	return (FALSE);
}
