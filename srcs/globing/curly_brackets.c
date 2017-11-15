#include "glob.h"
#include "list.h"
#include "libft.h"
#include <stdio.h>

void	curly_brackets_coma(t_list **res, char *expr, char *str, int end)
{
	char	**splited;
	int		i;

	i = 0;
	splited = ft_strsplit_coma_bracket(str);
	while (splited[i])
	{
		curly_brackets(res, \
				ft_strjoin3_free(expr, splited[i], expr + end + 1, 0), end + 1);
		i++;
	}
	ft_arraydel(&splited);
	free(str);
	free(expr);
}

int		change_state_quote(char c, int quoted)
{
	if (c == '\'' && quoted != 3)
	{
		if (quoted == 0)
			quoted = 1;
		else if (quoted == 1)
			quoted = 0;
	}
	else if (c == '"' && quoted != 3)
	{
		if (quoted == 0)
			quoted = 2;
		else if (quoted == 2)
			quoted = 0;
	}
	else if (c == '\\')
	{
		if (quoted == 0)
			quoted = 3;
		else if (quoted == 3)
			quoted = 0;
	}
	else
	{
		if (quoted == 3)
			quoted = 0;
	}
	return quoted;
}

int		get_end_bracket(char *expr, int offset)
{
	int		depth;
	size_t	i;
	int		quoted = 0;

	depth = 0;
	i = offset;
	while (expr[i])
	{
		if (expr[i] == '{' && quoted == 0)
			depth++;
		if (expr[i] == '}' && quoted == 0)
			depth--;
		if (depth == 0)
			return (i);
		quoted = change_state_quote(expr[i], quoted);
//		fprintf(stderr, "end_bracket quoted: %d, %c\n", quoted, expr[i]);
		i++;
	}
	return (-1);
}

/*
 ** find first '{' wich is not backslashed
 */

int		get_start_bracket(char *expr, int offset)
{
	size_t	i;
	int		quoted = 0;

	i = offset;
	while (expr[i])
	{
		if (expr[i] == '{' && quoted == 0)
			return (i);
		quoted = change_state_quote(expr[i], quoted);
//		fprintf(stderr, "start quoted: %d, %c\n", quoted, expr[i]);
		i++;
	}
	return (-1);
}

/*
 ** get start and end of pattern {-}, increase start until there il a closing '}'
 ** whith the same depth : "{1,{1..10}"
 ** here start will point to {1..10} at the end of the loop
 */

void	curly_brackets(t_list **res, char *expr, int offset)
{
	int		start;
	int		end;
	char	*str;

	start = -1;
	end = -1;
	start = get_start_bracket(expr, offset);
	while (start != -1 && (end = get_end_bracket(expr, start)) == -1)
		start = get_start_bracket(expr, start + 1);
	if (start == -1 || end == -1)
	{
		ft_simple_lst_pushback(res, ft_simple_lst_create(expr));
		return ;
	}
	str = ft_strndup(expr + start + 1, end - start - 1);
	*(expr + start) = '\0';
	if (curly_brackets_is_range(str))
		return (curly_brackets_range(res, expr, str, end));
	if (ft_strchr(str, ','))
		return (curly_brackets_coma(res, expr, str, end));
	*(expr + start) = '{';
	curly_brackets(res, expr, end);
}

t_list	*expand_curly_brackets(char *expr)
{
	t_list *res;

	res = NULL;
	curly_brackets(&res, ft_strdup(expr), 0);
	return (res);
}
