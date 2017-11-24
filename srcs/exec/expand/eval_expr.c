#include "expand.h"

char		*skip_white_space(char *str)
{
	while (*str && ft_is_space(*str))
		str++;
	return (str);
}

int			eval_expr_val(char **expr, long int *result)
{
	char		*digit;
	int			depth;

	depth = 0;
	if (*(digit = skip_white_space(*expr)) == '(')
	{
		++digit;
		while (**expr)
		{
			if (**expr == ')' && --depth == 0)
				break ;
			else if (**expr == '(')
				depth++;
			(*expr)++;
		}
		if (!**expr)
			return (WRDE_SYNTAX);
		*(*expr)++ = 0;
		if (eval_expr(digit, result))
			return (WRDE_SYNTAX);
		return (0);
	}
	if (!ft_atoilong_safe(digit, expr, result))
		return (WRDE_SYNTAX);
	return (0);
}

int			eval_expr_multdiv(char **expr, long int *result)
{
	long int		arg;

	if (eval_expr_val(expr, result) != 0)
		return (WRDE_SYNTAX);
	while (**expr)
	{
		*expr = skip_white_space(*expr);
		if (**expr == '*')
		{
			++(*expr);
			if (eval_expr_val(expr, &arg) != 0)
				return (WRDE_SYNTAX);
			*result *= arg;
		}
		else if (**expr == '/')
		{
			++(*expr);
			if (eval_expr_val(expr, &arg) != 0 || arg == 0)
				return (WRDE_SYNTAX);
			*result /= arg;
		}
		else
			break ;
	}
	return (0);
}

int			eval_expr(char *expr, long int *result)
{
	long			arg;

	if (eval_expr_multdiv(&expr, result) != 0)
		return (WRDE_SYNTAX);
	while (*expr)
	{
		expr = skip_white_space(expr);
		if (*expr == '+')
		{
			++expr;
			if (eval_expr_multdiv(&expr, &arg) != 0)
				return (WRDE_SYNTAX);
			*result += arg;
		}
		else if (*expr == '-')
		{
			++expr;
			if (eval_expr_multdiv(&expr, &arg) != 0)
				return (WRDE_SYNTAX);
			*result -= arg;
		}
		else
			break ;
	}
	return (0);
}
