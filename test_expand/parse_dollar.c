#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

#define CHAR_IN_SET(c, str) ft_strchr(str, c) != NULL

int		parse_param (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted)
{
	size_t start = *offset;
	char *value = NULL;
	int seen_hash = 0;
	int free_value = 0;
	int special = 0;
	char buffer[21];
	int brace = words[*offset] == '{';
	t_word env;
	w_newword (&env);
	if (brace)
		++*offset;
	if (words[*offset] == '#')
	{
		seen_hash = 1;
		++*offset;
	}
	if (ft_isalpha (words[*offset]) || words[*offset] == '_')
	{
		/* Normal parameter name. */
		while (ft_isalnum (words[*offset]) || words[*offset] == '_')
		{
			w_addchar (&env, words[*offset]);
			++*offset;
		}
		--*offset;
	}
	else if (ft_isdigit (words[*offset]))
	{
		/* Numeric parameter name. */
		special = 1;
		while (ft_isdigit(words[*offset]))
		{
			w_addchar (&env, words[*offset]);
			++*offset;
			if (!brace)
				break ;
		}
		--*offset;
	}
	else if (CHAR_IN_SET (words[*offset], "*@$"))
	{
		/* Special parameter. */
		special = 1;
		w_addchar (&env, words[*offset]);
		++*offset;
	}
	if (env.str == NULL)
	{
		if (seen_hash)
		{
			/* $# expands to the number of positional parameters */
			buffer[20] = '\0';
			value = ft_itoa (42);
			seen_hash = 0;
		}
		else
		{
			/* Just $ on its own */
			*offset = start - 1;
			w_addchar (word, '$');
			w_addchar (g_word, '$');
			return 0;
		}
	}
	/* Is it a numeric parameter? */
	else if (ft_isdigit (env.str[0]))
	{
		int n = ft_atoi (env.str);

		if (n >= 42)
			/* Substitute NULL. */
			value = NULL;
		else
			/* Replace with appropriate positional parameter. */
			value = "42";
	}
	else
	{
		printf("env.str: {%s}\n", env.str);
		value = getenv (env.str);
	}
	w_free(&env);
	if (seen_hash)
	{
		char *param_length = ft_itoa (value ? strlen (value) : 0);
		w_addstr (word, param_length);
		free(param_length);
		if (free_value)
			free (value);
		return 0;
	}
	if (value == NULL)
		return 0;
	if (quoted || !exp)
	{
		size_t		i = 0;
		while (value[i])
		{
			if (value[i] == '\\')
				parse_qtd_backslash (g_word, word, value, &i); //TODO: effet de bord
			else if (ft_strchr("*[?", value[i]))
			{
				w_addchar (g_word, '\\');
				w_addchar (g_word, value[i]); 
				w_addchar (word, value[i]);
			}
			else
			{
				w_addchar (g_word, value[i]);
				w_addchar (word, value[i]);
			}
			++(*offset);
		}
		if (free_value)
			free (value);
		return 0;
	}
	else
	{
		/* Need to field-split */
		char	**split = ft_strsplit(value, ifs);
		size_t		i;
		w_addstr (word, split[0]);
		w_addstr (g_word, split[0]);
		i = 1;
		while (split[i])
		{
			w_addword (exp, g_word, word);
			printf("split[i]: %s\n", split[i]);
			w_addstr (word, split[i]);
			w_addstr (g_word, split[i]);
			i++;
		}
		if (free_value)
			free (value);
		ft_arraydel(&split);
	}
	return 0;
}

int		parse_dollars (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted)
{
	if (words[1 + *offset] == '"' || words[1 + *offset] == '\\' || words[1 + *offset] == '\0')
	{
		w_addchar (word, '$');
		return 0;
	}

	/*case { ou deffault*/
	else
	{
		++(*offset);
		return parse_param (g_word, word, words, offset,
				exp, ifs, quoted);
	}
}
