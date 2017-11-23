	/* Is it a special parameter? */
	else if (special)
	{
		/* Is it `$$'? */
		if (*env == '$')
		{
			buffer[20] = '\0';
			value = _itoa_word(__getpid(), &buffer[20], 10, 0);
		}
		/* Is it `${#*}' or `${#@}'? */
		else if ((*env == '*' || *env == '@') && seen_hash)
		{
			buffer[20] = '\0';
			value = _itoa_word(__libc_argc > 0 ? __libc_argc - 1 : 0,
					&buffer[20], 10, 0);
			*word = w_addstr(*word, word_length, max_length, value);
			free(env);
			free(pattern);
			return *word ? 0 : WRDE_NOSPACE;
		}
		/* Is it `$*' or `$@'(unquoted) ? */
		else if (*env == '*' ||(*env == '@' && !quoted))
		{
			size_t plist_len = 0;
			int p;
			char *end;

			/* Build up value parameter by parameter(copy them) */
			for(p = 1; __libc_argv[p]; ++p)
				plist_len += strlen(__libc_argv[p]) + 1; /* for space */
			value = malloc(plist_len);
			if (value == NULL)
				goto no_space;
			end = value;
			*end = 0;
			for(p = 1; __libc_argv[p]; ++p)
			{
				if (p > 1)
					*end++ = ' ';
				end = __stpcpy(end, __libc_argv[p]);
			}

			free_value = 1;
		}
		else
		{
			/* Each parameter is a separate word("$@") */
			if (__libc_argc == 2)
				value = __libc_argv[1];
			else if (__libc_argc > 2)
			{
				int p;

				/* Append first parameter to current word. */
				value = w_addstr(*word, word_length, max_length,
						__libc_argv[1]);
				if (value == NULL || w_addword(pwordexp, value))
					goto no_space;

				for(p = 2; __libc_argv[p + 1]; p++)
				{
					char *newword = __strdup(__libc_argv[p]);
					if (newword == NULL || w_addword(pwordexp, newword))
						goto no_space;
				}

				/* Start a new word with the last parameter. */
				*word = w_newword(word_length, max_length);
				value = __libc_argv[p];
			}
			else
			{
				free(env);
				free(pattern);
				return 0;
			}
		}
	}

