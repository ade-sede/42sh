#include <stdio.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "local.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

/*  after "$" */

int		parse_param (t_expand *exp)
{
	size_t start = exp->offset;
	char *value = NULL;
	int seen_hash = 0;
	int special = 0;
	int brace = exp->words[exp->offset] == '{';
	t_word env;
	w_newword (&env);
	if (brace)
		++exp->offset;
	if (exp->words[exp->offset] == '#')
	{
		seen_hash = 1;
		++exp->offset;
	}
	if (ft_isalpha (exp->words[exp->offset]) || exp->words[exp->offset] == '_')
	{
		/* Normal parameter name. */
		while (ft_isalnum (exp->words[exp->offset]) || exp->words[exp->offset] == '_')
		{
			w_addchar (&env, exp->words[exp->offset]);
			++exp->offset;
		}
		--exp->offset;
	}
	else if (ft_isdigit (exp->words[exp->offset]))
	{
		/* Numeric parameter name. */
		special = 1;
		while (ft_isdigit(exp->words[exp->offset]))
		{
			w_addchar (&env, exp->words[exp->offset]);
			++exp->offset;
			if (!brace)
				break ;
		}
		--exp->offset;
	}
	else if (CHAR_IN_SET (exp->words[exp->offset], "*@$"))
	{
		/* Special parameter. */
		special = 1;
		w_addchar (&env, exp->words[exp->offset]);
		++exp->offset;
	}
	if (env.str == NULL)
	{
		if (seen_hash)
		{
			value = ft_strdup(var_get_value (singleton_env(), "#"));
			seen_hash = 0;
		}
		else
		{
			/* Just $ on its own */
			exp->offset = start - 1;
			w_addchar (&exp->word, '$');
			w_addchar (&exp->g_word, '$');
			return 0;
		}
	}
	else
	{
		//fprintf(stderr,"env.str: {%s}\n", env.str);
		value = ft_strdup(var_get_value (singleton_env(), env.str));
	}
	w_free(&env);
	if (seen_hash)
	{
		char *param_length = ft_itoa (value ? strlen (value) : 0);
		w_addstr (&exp->word, param_length);
		free (param_length);
		free (value);
		return 0;
	}
	if (value == NULL)
		return 0;
	handle_fieldsplitting(value, exp);
	free (value);
	return 0;
}

/*  on "$" */

int		parse_dollars (t_expand *exp)
{
	if (exp->words[1 + exp->offset] == '"' || exp->words[1 + exp->offset] == '\\' || exp->words[1 + exp->offset] == '\0')
	{
		w_addchar (&exp->word, '$');
		return 0;
	}
	
	if (exp->words[1 + exp->offset] == '(')
	{
		if (exp->words[2 + exp->offset] == '(')
		{
			/* Differentiate between $((1+3)) and $((echo);(ls)) */
			int i = 3 + exp->offset;
			int depth = 0;
			while (exp->words[i] && !(depth == 0 && exp->words[i] == ')'))
			{
				if (exp->words[i] == '(')
					++depth;
				else if (exp->words[i] == ')')
					--depth;

				++i;
			}

			if (exp->words[i] == ')' && exp->words[i + 1] == ')')
			{
				(exp->offset) += 3;
				/* Call parse_arith -- 0 is for "no brackets" */
				//return parse_arith (&exp->word, word_length, max_length, words, offset,
//						exp->flags, 0);
				return 0;
			}
		}
		//fprintf(stderr,"parse dollar command substitution\n");
		(exp->offset) += 2;
		return parse_comm (exp);
	}
	/*case { ou deffault*/
	else
	{
		++(exp->offset);
		return parse_param (exp);
	}
}
