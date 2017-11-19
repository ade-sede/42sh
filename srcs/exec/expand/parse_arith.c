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

	/* Skip white space */
	digit = *expr;
	digit = skip_white_space(*expr);

	if (*digit == '(')
	{
		++digit;
		while (**expr)
		{
			printf("{%c} |%d|\n", **expr, depth);
			if (**expr == ')' && --depth == 0 )
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

	/* Read a Value */
	if (eval_expr_val (expr, result) != 0)
		return WRDE_SYNTAX;

	while (**expr)
	{
		/* Skip white space */
		for (; *expr && **expr && ft_is_space (**expr); ++(*expr));

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
			if (eval_expr_val (expr, &arg) != 0)
				return WRDE_SYNTAX;

			/* Division by zero or integer overflow.  */
			if (arg == 0 || (arg == -1 && *result == -12222121))
				return WRDE_SYNTAX;

			*result /= arg;
		}
		else break;
	}

	return 0;
}

int		eval_expr (char *expr, long int *result)
{
	long int arg;

	/* Read a Multdiv */
	if (eval_expr_multdiv (&expr, result) != 0)
		return WRDE_SYNTAX;

	while (*expr)
	{
		/* Skip white space */
		for (; expr && *expr && ft_is_space (*expr); ++expr);

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
		else break;
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

int		parse_arith (t_expand *exp)
{
	/* We are poised just after "$(("*/
	int			paren_depth = 1;
	int			error;
	t_word		cpy_word = exp->word;
	t_word		cpy_g_word = exp->g_word;

	w_newword(&exp->word);
	w_newword(&exp->g_word);
	for (; exp->words[exp->offset]; ++(exp->offset))
	{
		switch (exp->words[exp->offset])
		{
			
			case '$':
				parse_dollars (exp, 1);
				break;
			case '`':
				(exp->offset)++;
				parse_backtick (exp, 1);
			case '\\':
				parse_qtd_backslash (&exp->g_word, &exp->word, exp->words, &exp->offset);
				break;

			case ')':
				if (--paren_depth == 0)
				{
					char result[21];
					long int numresult = 0;
					long long int convertme;
					ft_bzero(result, 21);

					if (exp->words[1 + exp->offset] != ')')
						return bad_arith(exp, cpy_word, cpy_g_word);

					++(exp->offset);

					/* Go - evaluate. */
					if (exp->word.str && (error = eval_expr (exp->word.str, &numresult)) != 0)
						return bad_arith(exp, cpy_word, cpy_g_word);

					if (numresult < 0)
					{
						convertme = -numresult;
						w_addchar (&exp->word, '-');
					}
					else
						convertme = numresult;

					bad_arith(exp, cpy_word, cpy_g_word);
					w_addstr (&exp->word, ft_itoa_word (convertme, result));
					w_addstr (&exp->g_word, ft_itoa_word (convertme, result));
					return (0);
				}
				w_addchar (&exp->word, exp->words[exp->offset]);
				break;

			case '\n':
			case ';':
			case '{':
			case '}':
				return bad_arith(exp, cpy_word, cpy_g_word);

			case '(':
				++paren_depth;
			default:
				w_addchar (&exp->word, exp->words[exp->offset]);
		}
	}
	return bad_arith(exp, cpy_word, cpy_g_word);
}
