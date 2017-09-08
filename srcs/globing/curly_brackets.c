#include "glob.h"
#include "list.h"
#include "libft.h"
#include <stdio.h>

int	ft_is_start_of_digit(char c)
{
	return (ft_isdigit(c) || c == '-');
}

int	curly_brackets_is_range(char *str)
{
	int	start_range;
	int	end_range;
	int	i;
	char	*point;
	int	is_number;

	//printf("patern: %s\n", str);
	if (!(point = ft_strchr(str, '.')))
		return (0);
	*point = '\0';
	is_number = ft_atoi_safe(str, &start_range);
	*point = '.';
	if (!is_number)
	{
		if (!(str[0] && str[1] && str[2] && str[3] && str[1] == '.' && str[2] == '.' && !str[4]))
			return (0);
		return (1);
	}
	i = 0;
	while (str[i] && (ft_is_start_of_digit(str[i])))
		i++;
	if (str[i] != '.' || str[i + 1] != '.')
		return (0);
	i += 2;
	////printf("str %s\n", str + i);
	if (!(ft_atoi_safe(str + i, &end_range)) && (str[i + 1] || ((start_range >= 10 || start_range <= 10) && !str[i + 1])))
		return (0);
	//printf("star_range: %d, end_range: %d\n", start_range, end_range);
	return (1);
}

void	curly_brackets_range_alpha(t_list **res, char *expr, char *str, int end)
{
	char	b[2];
	char	b_end;

	b[0] = str[0];
	b[1] = '\0';
	b_end = str[ft_strlen(str) - 1];
	//printf("expr: %s, b: %s, b_end: %c\n", expr, b, b_end);
	while (b[0] <= b_end)
	{
		curly_brackets(res, ft_strjoin3_free(expr, (char *)b, expr + end + 1, 0));
		(*b)++;
	}
	free(str);
	free(expr);
}

void	curly_brackets_range_num(t_list **res, char *expr, char *str, int end)
{
	int	i;
	int	start_range;
	int	end_range;

	ft_atoi_safe(str, &start_range);
	i = 0;
	while (ft_is_start_of_digit(str[i]))
		i++;
	i += 2;
	ft_atoi_safe(str + i, &end_range);
	//printf("star_range: %d, end_range: %d,\n", start_range, end_range);
	if (start_range <= end_range)
	{
		while (start_range <= end_range)
		{
			curly_brackets(res, ft_strjoin3_free(expr, ft_itoa(start_range), expr + end + 1, 2));
			start_range++;
		}
	}
	else
	{
		while (start_range >= end_range)
		{
			curly_brackets(res, ft_strjoin3_free(expr, ft_itoa(start_range), expr + end + 1, 2));
			start_range--;
		}
	}
	free(str);
	free(expr);
}

void	curly_brackets_range(t_list **res, char *expr, char *str, int end)
{
	//printf("it's a range\n");
	if (!ft_is_start_of_digit(str[0]) || !ft_isdigit(str[ft_strlen(str) - 1]))
		return (curly_brackets_range_alpha(res, expr, str, end));
	return (curly_brackets_range_num(res, expr, str, end));
}

void	curly_brackets_coma(t_list **res, char *expr, char *str, int end)
{
	char	**splited;
	int	i;
	
	i = 0;
	splited = ft_strsplit_coma_bracket(str);
	while (splited[i])
	{
		//printf("splited : %s\n", splited[i]);
		curly_brackets(res, ft_strjoin3_free(expr, splited[i], expr + end + 1, 0));
		i++;
	}
	ft_arraydel(&splited);
	free(str);
	free(expr);
}

int	get_end_bracket(char *expr)
{
	int	depth;
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
	int	start;
	int	end;
	char	*str;

	start = -1;
	end = -1;
	start = ft_strichr(expr, '{');
	if (start != -1 && (end = get_end_bracket(expr + start)) != -1)
		end += start;
	if (start == -1 || end == -1) // condition d arret tt les fonction rappele curlu brackets
	{
		ft_simple_lst_add(res, ft_simple_lst_create(expr));
		return ;
	}
	str = ft_strndup(expr + start + 1, end - start - 1);
	*(expr + start) = '\0';
	if (curly_brackets_is_range(str))
		return (curly_brackets_range(res, expr, str, end));
	return (curly_brackets_coma(res, expr, str, end));
}

t_list	*expand_curly_brackets(char *expr)
{
	t_list *res;

	res = NULL;
	curly_brackets(&res, ft_strdup(expr));
	return (res);
}
