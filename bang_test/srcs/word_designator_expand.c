#include "bang.h"
#include "libft.h"


#include <stdio.h>
static int valid_designator(const char **source, int *done)
{
	if (**source == 0 || ft_strchr(" 	\n", **source))
	{
		*done = FALSE;
		return (FALSE);
	}
	if (**source == ':')
	{
		++(*source);
		if (!ft_strchr("^$-*", **source) && !ft_isdigit(**source))
		{
			*done = FALSE;
			return (TRUE);
		}
	}
	else if (!ft_strchr("^$-*", **source))
		return (TRUE);
	return (FALSE);
}

static void parse_end(const char **source, int *start, int *end)
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

static void	parse_range(const char **source, int *start, int *end)
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
	else if (ft_isdigit(**source))
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

static void fake_lex(const char *source, t_list **list)
{
	char	**ret;

	ret = ft_strsplit(source, " 	");
	if (!ret)
	{
		*list = NULL;
		return ;
	}
	for (int i = 0 ; ret[i] ; ++i)
	{
		ft_simple_lst_pushback(list, ft_simple_lst_create(ft_strdup(ret[i])));
		free(ret[i]);
	}
	free(ret);
}

static int	extract_words(int start, int end, t_word event, t_word *word_designator)
{
	t_list	*start_node;
	t_list	*end_node;
	t_list	*list;

	list = NULL;
	if (start > end && end != -1 && end != -2)
		return (TRUE);
	fake_lex(event.str, &list);
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
		ft_simple_lst_remove(&list, ft_free);
		return (TRUE);
	}
	while (start_node && start_node != end_node->next)
	{
		w_addstr(word_designator, start_node->data);
		w_addchar(word_designator, ' ');
		start_node = start_node->next;
	}
	word_designator->str[word_designator->actlen - 1] = 0;
	--word_designator->actlen;
	ft_simple_lst_remove(&list, ft_free);
	return (FALSE);
}

static int default_behavior(t_word *word_designator, t_word event)
{
	if (event.str)
		w_addstr(word_designator, event.str);
	return (FALSE);
}

int	word_designator_expand(const char **source, t_word event, t_word *word_designator, int *done)
{
	int	ret;
	int	start;
	int	end;

	start = -3;
	end = -3;
	*done = TRUE;
	w_newword(word_designator);
	ret = valid_designator(source, done);
	if (!*done)
		return (default_behavior(word_designator, event));
	if (ret)
		return (TRUE);
	parse_range(source, &start, &end);
	if (extract_words(start, end, event, word_designator))
		return (TRUE);
	return (FALSE);
}
