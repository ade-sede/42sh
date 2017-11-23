#include "glob.h"
#include "list.h"
#include "libft.h"

static void	free_arg(char *expr, char *str)
{
	ft_strdel(&str);
	ft_strdel(&expr);
}

void		curly_brackets_range_alpha(t_list **res, char *expr, char *str, \
		int end)
{
	char	b[2];
	char	b_end;
	char	*new_str;

	b[0] = str[0];
	b[1] = '\0';
	b_end = str[ft_strlen(str) - 1];
	if (b[0] <= b_end)
	{
		while (b[0] <= b_end)
		{
			new_str = ft_strjoin3_free(expr, (char *)b, expr + end + 1, 0);
			curly_brackets(res, new_str, ft_strlen(expr) + ft_strlen(b));
			(*b)++;
		}
		return (free_arg(expr, str));
	}
	while (b[0] >= b_end)
	{
		new_str = ft_strjoin3_free(expr, (char *)b, expr + end + 1, 0);
		curly_brackets(res, new_str, ft_strlen(expr) + ft_strlen(b));
		(*b)--;
	}
	free_arg(expr, str);
}

void		curly_brackets_range_num(t_list **res, char *expr, char *str, \
		int end)
{
	int		i;
	int		start_range;
	int		end_range;
	char	*new_str;

	ft_atoi_safe(str, &start_range);
	i = 0;
	while (ft_is_start_of_digit(str[i]))
		i++;
	i += 2;
	ft_atoi_safe(str + i, &end_range);
	while (start_range != end_range)
	{
		ft_itoa_word(start_range, itoa_res);
		new_str = ft_strjoin3_free(expr, (char *)itoa_res, expr + end + 1, 0);
		curly_brackets(res, new_str, ft_strlen(expr) + ft_strlen(itoa_res));
		(start_range < end_range) ? start_range++ : start_range--;
	}
	ft_itoa_word(start_range, itoa_res);
	new_str = ft_strjoin3_free(expr, (char *)itoa_res, expr + end + 1, 0);
	curly_brackets(res, new_str, ft_strlen(expr) + ft_strlen(itoa_res));
	free(str);
	free(expr);
}

void		curly_brackets_range(t_list **res, char *expr, char *str, int end)
{
	if (!ft_is_start_of_digit(str[0]) || !ft_isdigit(str[ft_strlen(str) - 1]))
		return (curly_brackets_range_alpha(res, expr, str, end));
	return (curly_brackets_range_num(res, expr, str, end));
}
