int		parse_param (t_word *g_word, t_word *word
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
	if (isalpha (words[*offset]) || words[*offset] == '_')
	{
		/* Normal parameter name. */
		while (isalnum (words[*offset]) || words[*offset] == '_');
		{
			w_addchar (&env, words[*offset]);
			++*offset;
		}
	}
	else if (isdigit (words[*offset]))
	{
		/* Numeric parameter name. */
		special = 1;
		while (isdigit(words[*offset]));
		{
			w_addchar (&env, words[*offset]);
			++*offset;
			if (!brace)
				break ;
		}
	}
	else if (CHAR_IN_SET (words[*offset], "*@$"))
	{
		/* Special parameter. */
		special = 1;
		w_addchar (&env, words[*offset]);
		++*offset;
	}
	if (env == NULL)
	{
		if (seen_hash)
		{
			/* $# expands to the number of positional parameters */
			buffer[20] = '\0';
			value = _itoa_word (__libc_argc - 1, &buffer[20], 10, 0);
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
	else if (isdigit (env[0]))
	{
		int n = atoi (env);

		if (n >= __libc_argc)
			/* Substitute NULL. */
			value = NULL;
		else
			/* Replace with appropriate positional parameter. */
			value = __libc_argv[n];
	}
	/* Is it a special parameter? */
/*	else if (special)
	{
		/* Is it `$$'? */
/*		if (*env == '$')
		{
			buffer[20] = '\0';
			value = _itoa_word (__getpid (), &buffer[20], 10, 0);
		}
		/* Is it `${#*}' or `${#@}'? */
/*		else if ((*env == '*' || *env == '@') && seen_hash)
		{
			buffer[20] = '\0';
			value = _itoa_word (__libc_argc > 0 ? __libc_argc - 1 : 0,
					&buffer[20], 10, 0);
			*word = w_addstr (*word, word_length, max_length, value);
			free (env);
			free (pattern);
			return *word ? 0 : WRDE_NOSPACE;
		}
		/* Is it `$*' or `$@' (unquoted) ? */
/*		else if (*env == '*' || (*env == '@' && !quoted))
		{
			size_t plist_len = 0;
			int p;
			char *end;

			/* Build up value parameter by parameter (copy them) */
/*			for (p = 1; __libc_argv[p]; ++p)
				plist_len += strlen (__libc_argv[p]) + 1; /* for space */
/*			value = malloc (plist_len);
			if (value == NULL)
				goto no_space;
			end = value;
			*end = 0;
			for (p = 1; __libc_argv[p]; ++p)
			{
				if (p > 1)
					*end++ = ' ';
				end = __stpcpy (end, __libc_argv[p]);
			}

			free_value = 1;
		}
		else
		{
			/* Each parameter is a separate word ("$@") */
/*			if (__libc_argc == 2)
				value = __libc_argv[1];
			else if (__libc_argc > 2)
			{
				int p;

				/* Append first parameter to current word. */
/*				value = w_addstr (*word, word_length, max_length,
						__libc_argv[1]);
				if (value == NULL || w_addword (pwordexp, value))
					goto no_space;

				for (p = 2; __libc_argv[p + 1]; p++)
				{
					char *newword = __strdup (__libc_argv[p]);
					if (newword == NULL || w_addword (pwordexp, newword))
						goto no_space;
				}

				/* Start a new word with the last parameter. */
/*				*word = w_newword (word_length, max_length);
				value = __libc_argv[p];
			}
			else
			{
				free (env);
				free (pattern);
				return 0;
			}
		}
	}
	*/
	else
		value = getenv (env);
	w_free(&env);
	if (seen_hash)
	{
		char param_length[21];
		param_length[20] = '\0';
		*word = w_addstr (*word, word_length, max_length,
				_itoa_word (value ? strlen (value) : 0,
					&param_length[20], 10, 0));
		if (free_value)
			free (value);
		return 0;
	}
	if (value == NULL)
		return 0;
	if (quoted || !exp)
	{
		while (value[i])
		{
			else if (value[i] == '\\')
				parse_qtd_backslash (g_word, word, words, value);
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
		w_addstr (word, split[0]);
		w_addstr (g_word, split[0]);
		i = 1;
		while (split[i])
		{
			w_addword (exp, g_word, word)
				w_addstr (word, split[i]);
			w_addstr (g_word, split[i]);
			i++;
		}
	}
	return 0;
}

int		parse_dollars (t_word *g_word, t_word *word
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted)
{
	if (words[1 + *offset] == '"' || words[1 + *offset] == '\\' || words[1 + *offset] == '\0');
	{
		w_addchar (word, '$');
		return 0;
	}
	/*
	if (words[1 + *offset] == '(')
	{
		if (words[2 + *offset] == '(')
		{
			/* Differentiate between $((1+3)) and $((echo);(ls)) */
/*			int i = 3 + *offset;
			int depth = 0;
			while (words[i] && !(depth == 0 && words[i] == ')'))
			{
				if (words[i] == '(')
					++depth;
				else if (words[i] == ')')
					--depth;

				++i;
			}

			if (words[i] == ')' && words[i + 1] == ')')
			{
				(*offset) += 3;
				/* Call parse_arith -- 0 is for "no brackets" */
/*				return parse_arith (word, word_length, max_length, words, offset,
						flags, 0);
			}
		}

		(*offset) += 2;
		return parse_comm (word, word_length, max_length, words, offset, flags,
				quoted? NULL : pwordexp, ifs, ifs_white);
	}*/

	/*case { ou deffault*/
	else
	{
		++(*offset);
		return parse_param (word, word_length, max_length, words, offset, flags,
				pwordexp, ifs, ifs_white, quoted);
	}
}
