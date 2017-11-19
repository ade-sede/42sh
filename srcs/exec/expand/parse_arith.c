#include "expand.h"
# define WRDE_BADCHAR 5

char	*skip_white_space(char *str)
{
	while (*str && ft_is_space(*str))
		str++;
	return (str);
}

int		eval_expr_val (char **expr, long int *result)
{
	char	*digit;
	int		depth = 0;

	digit = skip_white_space(*expr);
	if (*digit == '(')
	{
		++digit;
		while (**expr)
		{
			if (**expr == ')' && --depth == 0)
				break;
			else if (**expr == '(')
				depth++;
			(*expr)++;
		}
		if (!**expr)
			return WRDE_SYNTAX;
		*(*expr)++ = 0;
		if (eval_expr (digit, result))
			return WRDE_SYNTAX;
		return 0;
	}
	if (!ft_atoilong_safe(digit, expr, result))
		return WRDE_SYNTAX;
	return 0;
}

int		eval_expr_multdiv (char **expr, long int *result)
{
	long int arg;

	if (eval_expr_val (expr, result) != 0)
		return WRDE_SYNTAX;
	while (**expr)
	{
		*expr = skip_white_space(*expr); 
		if (**expr == '*')
		{
			++(*expr);
			if (eval_expr_val (expr, &arg) != 0)
				return WRDE_SYNTAX;
			*result *= arg;
		}
		else if (**expr == '/')
		{
			++(*expr);
			if (eval_expr_val (expr, &arg) != 0 || arg == 0)
				return WRDE_SYNTAX;
			*result /= arg;
		}
		else
			break;
	}
	return 0;
}

int		eval_expr (char *expr, long int *result)
{
	long arg;

	if (eval_expr_multdiv (&expr, result) != 0)
		return WRDE_SYNTAX;
	while (*expr)
	{
		expr = skip_white_space(expr); 
		if (*expr == '+')
		{
			++expr;
			if (eval_expr_multdiv (&expr, &arg) != 0)
				return WRDE_SYNTAX;
			*result += arg;
		}
		else if (*expr == '-')
		{
			++expr;
			if (eval_expr_multdiv (&expr, &arg) != 0)
				return WRDE_SYNTAX;
			*result -= arg;
		}
		else
			break;
	}
	return 0;
}

int		bad_arith(t_expand *exp, t_word cpy_word, t_word cpy_g_word)
{
	w_free(&exp->word);
	w_free(&exp->g_word);
	exp->word = cpy_word;
	exp->g_word = cpy_g_word;
	return (WRDE_SYNTAX);
}

int	get_arith(t_expand *exp, t_word cpy_word, t_word cpy_g_word)
{
	char			result[21];
	long int		numresult = 0;
	long long int	convertme;
	int				error;

	ft_bzero(result, 21);
	if (exp->words[1 + exp->offset] != ')')
		return bad_arith(exp, cpy_word, cpy_g_word);
	++(exp->offset);
	if (exp->word.str && (error = eval_expr (exp->word.str, &numresult)) != 0)
		return bad_arith(exp, cpy_word, cpy_g_word);
	bad_arith(exp, cpy_word, cpy_g_word);
	if (numresult < 0)
	{
		convertme = -numresult;
		w_addchar (&exp->word, '-');
	}
	else
		convertme = numresult;
	w_addstr (&exp->word, ft_itoa_word (convertme, result));
	w_addstr (&exp->g_word, ft_itoa_word (convertme, result));
	return (0);
}

int		parse_arith_special_chars (t_expand *exp, t_word cpy_word, t_word cpy_g_word)
{
	if (exp->words[exp->offset] == '$')
		parse_dollars (exp, 1);
	else if (exp->words[exp->offset] == '`')
	{
		(exp->offset)++;
		parse_backtick (exp, 1);
	}
	else if (exp->words[exp->offset] == '\\')
		parse_qtd_backslash (&exp->g_word, &exp->word, exp->words, &exp->offset);
	else if (ft_strchr("\n;{}",exp->words[exp->offset]))
		return bad_arith(exp, cpy_word, cpy_g_word);
	else
		w_addchar (&exp->word, exp->words[exp->offset]);
	return (0);
}

void	cpy_word_g_word(t_expand *exp, t_word *cpy_word, t_word *cpy_g_word)
{
	*cpy_word = exp->word;
	*cpy_g_word = exp->g_word;
	w_newword(&exp->word);
	w_newword(&exp->g_word);
}

int		parse_arith (t_expand *exp)
{
	int			paren_depth = 1;
	t_word		cpy_word;
	t_word		cpy_g_word;

	paren_depth = 1;
	cpy_word_g_word(exp, &cpy_word, &cpy_g_word);
	while (exp->words[exp->offset])
	{
		printf("parse arith{%c} |%d|\n", exp->words[exp->offset], paren_depth);
		if (exp->words[exp->offset] == ')')
		{
			if (--paren_depth == 0)
				return (get_arith(exp, cpy_word, cpy_g_word));
			w_addchar (&exp->word, exp->words[exp->offset]);
		}
		else if (exp->words[exp->offset] == '(')
		{
			w_addchar (&exp->word, exp->words[exp->offset]);
			++paren_depth;
		}
		else if (parse_arith_special_chars(exp, cpy_word, cpy_g_word) != 0)
			return (WRDE_SYNTAX);
		++(exp->offset);
	}
	return bad_arith(exp, cpy_word, cpy_g_word);
}
