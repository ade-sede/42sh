#define W_SIZE_BUFF        (100)
#define W_SIZE_ARRAY        (10)

typedef struct	s_word
{
	char		*str;
	size_t		actlen;
	size_t		maxlen;
}				t_word;

typedef struct	s_expand
{
	char		**av;
	size_t		actlen;
	size_t		maxlen;
}				t_expand;

void	w_newword (t_word *word)
{
  word->str = NULL;
  word->actlen = 0;
  word->maxlen = 0;
}

void	*ft_realloc(void *mem, size_t old_size, size_t new_size)
{
	void	*new_mem;

	new_mem = ft_memalloc(sizeof(new_size));
	memcpy(new_mem, mem, old_size);
	free(mem);
	return (new_mem);
}

char	*w_addchar (t_word *word, char ch)
{
	if (*word->actlen == *word->maxlen)
	{
		word->maxlen += W_CHUNK;
		word->str = (char *)ft_realloc (word->str, word->actlen, 1 + word->maxlen);
	}
	word->str[word->actlen] = ch;
	word->str[++(word->actlen)] = '\0';
	return (word->str);
}

char	*w_addmem (t_word *word, const char *str, size_t len)
{
	if (word->actlen + len > word->maxlen)
	{
		word->maxlen += MAX (2 * len, W_CHUNK);
		word->str = (char *)ft_realloc (word->str, word->actlen, 1 + word->maxlen);
	}
	memcpy(word->str[word->actlen], str, len);
	word->actlen += len;
	return (word->str);
}

char	*w_addstr (t_word *word, const char *str)
{
	size_t len;

	len = strlen (str);
	return (w_addmem(buffer, actlen, maxlen, str, len));
}

int		w_addword (t_expand *exp, char *word)
{
	int allocated;

	/* Internally, NULL acts like "".  Convert NULLs to "" before
	 * the caller sees them.
	 */
	if (exp->actlen == exp->maxlen)
	{
		exp->maxlen += W_SIZE_ARRAY;
		exp->av = (char **)ft_realloc(exp->we_wordv, sizeof(char *) * exp->act_len, 1 + word->maxlen);
	}
	allocated = false;
	if (word == NULL)
	{
		word = ft_strdup ("");
		allocated = true;
	}
	exp->av[exp->actlen] = word;
	exp->actlen += + 1;
	if (allocated)
		free(word);
}

int		w_newexp (t_expand *exp)
{
	exp->av = (char **)ft_memalloc(exp->we_wordv, sizeof(char *) * 1);
	exp->actlen = 0;
	exp->maxlen = 0;
}

int		parse_backslash (t_word *g_word, t_word *word, const char *words, size_t *offset)
{
	char	ch;

	ch = words[1 + *offset];
	if (ch == 0)
		return WRDE_SYNTAX;
	else
	{
		w_addchar (word, words[1 + *offset]);
		w_addchar (g_word, words[*offset]);
		w_addchar (g_word, words[1 + *offset]);
		++(*offset);
	}
	return 0;
}

int		parse_qtd_backslash (t_word *g_word, t_word *word, const char *words, size_t *offset)
{
	if (words[1 + *offset] == 0)
		return WRDE_SYNTAX;
	if (ft_strchr("$`\"\\", ch) != NULL)
	{
		w_addchar (word, words[1 + *offset]);
		w_addchar (g_word, words[*offset]);
		w_addchar (g_word, words[1 + *offset]);
		++(*offset);
	}
	else
	{
		w_addchar (word, words[*offset]);
		w_addchar (word, words[1 + *offset]);
		w_addchar (g_word, words[*offset]);
		w_addchar (g_word, words[1 + *offset]);
		++(*offset);
	}
	return 0;
}

int		parse_squote (t_word *g_word, t_word *word, const char *words, size_t *offset)
{
	while (words[*offset])
	{
		if (words[*offset] == '\'')
			return 0;
		/* backlash des caracteres de globing dans les quotes */
		if (ft_strchr("*[?\\", words[*offset]))
		{
			w_addchar (g_word, '\');
			w_addchar (g_word, words[*offset]); 
		}
		else
			w_addchar (g_word, words[*offset]);
		w_addchar (word, words[*offset]);
		++(*offset);
	}
	return WRDE_SYNTAX;
}

int		parse_dquote (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs)
{
	while (words[*offset])
	{
		if (words[*offset] == '"')
			return 0;
		else if (words[*offset] == '\')
			parse_qtd_backslash (g_word, word, words, offset);
		else if (words[*offset] == '$')
			parse_dollars (word, word_length, max_length, words, offset,
					flags, pwordexp, ifs, ifs_white, 1);
		else if (words[*offset] == '`')
		{
			++(*offset);
			error = parse_backtick (word, word_length, max_length, words,
					offset, flags, NULL, NULL, NULL);
		}
		else
		{
			w_addchar (g_word, words[*offset]);
			w_addchar (word, words[*offset]);
		}
		++(*offset);
	}
}
char	**wordexp (const char *words, )
{
	int	offset;
	t_word	word;
	t_word	g_word;
	int error;
	char *ifs;
	t_expand *exp;

	w_newword (&word);
	w_newexp (&exp);

	ifs = getenv ("IFS");

	if (ifs == NULL)
		ifs = ft_strdup(" \t\n");

	offset = 0;
	while (words[offset])
	{
		if (words[offset] == '\\')
			parse_backslash (&g_word, &word, words, &offset);
		else if (words[offset] == '"')
		{
			++offset;
			parse_dquote (&g_word, &word, words, &offset, exp, ifs);
			if (!word->actlength && !words[1 + offset])
				w_addword (exp, NULL);
		}
		else if (words[offset] == '\'')
		{
			++offset;
			parse_squote (&g_word, &word, words, &offset);
			if (!word->actlength && !words[1 + offset])
				w_addword (exp, NULL);
		}
		/*
		else if (words[offset] == '`')
		{
			++offset;
			parse_backtick (&word, &word_length, &max_length, words,
					&offset, flags, pwordexp, ifs,
					ifs_white);
		}
		else if (words[offset] == '$')
		{
			parse_dollars (&word, &word_length, &max_length, words,
					&offset, flags, pwordexp, ifs, ifs_white,
					0);
		}
		else if (words[offset] == '~')
		{
			parse_tilde (&word, &word_length, &max_length, words,
					&offset, pwordexp->we_wordc);
		}*/
		else
			word = w_addchar (word, &word_length, &max_length,
					ch);
		++offset;
	}
	if (word->str != NULL)
		w_addword (pwordexp, word);
}
