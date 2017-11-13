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
				ft_strjoin3_free(expr, splited[i], expr + end + 1, 0));
		i++;
	}
	ft_arraydel(&splited);
	free(str);
	free(expr);
}

int		get_end_bracket(char *expr)
{
	int		depth;
	size_t	i;

	depth = 0;
	i = 0;
	while (expr[i])
	{
		if (expr[i] == '{')
			depth++;
		if (expr[i] == '}')
			depth--;
		if (depth == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	curly_brackets(t_list **res, char *expr)
{
	int		start;
	int		end;
	char	*str;

	start = -1;
	end = -1;
	start = ft_strichr(expr, '{');
	if (start != -1 && (end = get_end_bracket(expr + start)) != -1)
		end += start;
	if (start == -1 || end == -1)
	{
		ft_simple_lst_pushback(res, ft_simple_lst_create(expr));
		return ;
	}
	str = ft_strndup(expr + start + 1, end - start - 1);
	*(expr + start) = '\0';
	if (curly_brackets_is_range(str))
		return (curly_brackets_range(res, expr, str, end));
	return (curly_brackets_coma(res, expr, str, end));
}

int		is_valid_curly_brackets(char *expr)
{
	int		depth;
	size_t	i;

	depth = 0;
	i = 0;
	while (expr[i])
	{
		if (expr[i] == '{')
			depth++;
		if (expr[i] == '}')
			depth--;
		i++;
	}
	return (depth == 0 ? 1 : 0);
}

t_list	*expand_curly_brackets(char *expr)
{
	t_list *res;

	res = NULL;
	if (!is_valid_curly_brackets(expr))
	{
		printf("bad curly bracket\n");
		return (res);
	}
	curly_brackets(&res, ft_strdup(expr));
	return (res);
}
