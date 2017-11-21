#include "libft.h"
#include "bang.h"



#include <stdio.h>
int	read_hist_numeric(int count, t_word *event, t_hist *hist)
{
	(void)count, (void)event, (void)hist;
	/* t_list_d	*start_point; */
	/* t_list_d	*event_node; */

	/* if (count == 0) */
	/* 	return (FALSE); */
	/* if (count < 0) */
	/* { */
	/* 	start_point = hist->list->first; */
	/* 	++count; */
	/* } */
	/* else */
	/* 	start_point = hist->list->last; */
	/* event_node = ft_double_lst_get_n(start_point, count); */
	/* if (!event_node) */
	/* 	return (TRUE); */
	/* w_addstr(event_node->line); */
	/* w_addstr(event, "0 1 2 3 4 5 6 7 8 9"); */
	w_addstr(event, "'1' '' '1' '' '' '2'\\''fd' '' '' '' ''\\'''");
	return (FALSE);
}

static	int	numeric_event(const char **source, t_word *event, t_hist *hist)
{
	int	err;
	int	count; err = FALSE;
	count = 0;
	if (**source == '!')
	{
		count = -1;
		++(*source);
	}
	else if (**source == '-')
	{
		count = ft_atoi_base((char*)*source, 10);
		++(*source);
		while (ft_isdigit(**source))
			++(*source);
	}
	else
	{
		count = ft_atoi_base((char*)*source, 10);
		while (ft_isdigit(**source))
			++(*source);
	}
	err = read_hist_numeric(count, event, hist);
	return (err);
}

static int read_hist_string(int flag, t_word string_event, t_word *event, t_hist *hist)
{
	(void)flag, (void)string_event, (void)event, (void)hist;
	/* t_list_t	*node; */

	/* node = hist->list->last; */
	/* if (!string_event.str) */
	/* 	return (TRUE); */
	/* if (flag == 1) */
	/* { */
	/* 	while (node && !ft_strstr(string_event.str, node->line)) */
	/* 		node = node->prev; */
	/* } */
	/* else */
	/* { */
	/* 	while node && !ft_strnequ(string_event.str, node->line, string_even.actlen)) */
	/* 		node = node->prev; */
	/* } */
	/* if (!node) */
	/* 	return (TRUE); */
	/* w_addstr(event, node->line); */
	w_addstr(event, "a b c d e f g h i k l m n o p q r s t u v w x y z a");
	return (FALSE);
}

static int	string_event(const char **source, t_word *event, t_hist *hist)
{
	t_word	string_event;
	int		flag;
	int		err;

	w_newword(&string_event);
	if (**source == '?')
	{
		++(*source);
		flag = 1;
		while (**source && !ft_strchr("?\n", **source))
		{
			w_addchar(&string_event, **source);
			++(*source);
		}
		if (**source == '?')
			++(*source);
	}
	else
	{
		flag = 2;
		while (**source && !ft_strchr(": 	\n", **source))
		{
			w_addchar(&string_event, **source);
			++(*source);
		}
	}
	//dprintf(2, "string_event.str = #%s#\n", string_event.str);
	err = read_hist_string(flag, string_event, event, hist);
	w_free(&string_event);
	return (err);
}

int	event_expand(const char *s, const char **source, t_word *event, t_hist *hist, int *done)
{
	int	err;

	err = FALSE;
	*done = TRUE;
	w_newword(event);
	if (ft_strchr("^$*-:", **source))
	{
		*done = FALSE;
		return (FALSE);
	}
	if (**source != '!' && **source != '-' && **source != '#' && **source != '?' && !ft_isalnum(**source))
		return (TRUE);
	if (**source == '!' || **source == '-' || ft_isdigit(**source))
	{
		if ((err = numeric_event(source, event, hist)))
		{
			//dprintf(2, "Num returned error");
			w_free(event);
			return (err);
		}
	}
	else if (**source == '?' || ft_isalpha(**source))
	{
		if ((err = string_event(source, event, hist)))
		{
			//dprintf(2, "String returned error");
			w_free(event);
			return (err);
		}
	}
	else
	{
		if (*source - s - 1 > 0)
			w_addmem(event, s, *source - s - 1);
		++(*source);
	}
	dprintf(2, "Event string = #%s#\n", event->str);
	return (err);
}
