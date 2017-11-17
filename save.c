void	curly_brackets(t_list **res, char *expr)
{
	int		start;
	int		start_tmp;
	int		end;
	char	*str;

	start = -1;
	end = -1;
	start = get_start_bracket(expr);
	while (start != -1)
	{
		end = get_end_bracket(expr + start);
		if (start != -1 && end != -1)
		{
			end += start;
			str = ft_strndup(expr + start + 1, end - start - 1);
			*(expr + start) = '\0';
			if (curly_brackets_is_range(str))
				return (curly_brackets_range(res, expr, str, end));
			if (ft_strchr(str, ','))
				return (curly_brackets_coma(res, expr, str, end));
			*(expr + start) = '{';
			free(str);
			start += end + 1;
			continue ;
		}
		start_tmp = start + 1;
		start = get_start_bracket(expr + start_tmp);
		if (start != -1)
			start += start_tmp;
	}
	if (start == -1 || end == -1)
	{
		ft_simple_lst_pushback(res, ft_simple_lst_create(expr));
		return ;
	}

