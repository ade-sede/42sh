#include "bang.h"
#include "libft.h"

struct s_parse_mod
{
	t_word	cache;
	t_word	tmp;
	int		quote_mode;
	int		g_flag;
};

static void	init_p(struct s_parse_mod *p, t_word word_designator)
{
	w_newword(&p->cache);
	w_newword(&p->tmp);
	if (word_designator.str)
		w_addstr(&p->cache, word_designator.str);
	p->quote_mode = 0;
	p->g_flag = 0;
}

static void	pop(t_word *old, t_word *new)
{
	w_free(old);
	w_newword(old);
	w_addstr(old, new->str);
	w_free(new);
	w_newword(new);
}

static int valid_modifier(const char **source, int *done)
{
	if (**source == ':')
	{
		++(*source);
		if (!**source || !ft_strchr("htreqxsg", **source))
			return (TRUE);
	}
	else
	{
		*done = FALSE;
		return (FALSE);
	}
	return (FALSE);
}

static int default_behavior(t_word *ret, t_word word_designator)
{
	if (word_designator.str)
		w_addstr(ret, word_designator.str);
	return (FALSE);
}

static int perform_substitute(struct s_parse_mod *p, t_word old, t_word new)
{
	size_t	i;
	size_t	len;
	int		done;

	if (!old.str)
		return (TRUE);
	i = 0;
	done = TRUE;
	len = ft_strlen(old.str);
	while (p->cache.str[i])
	{
		if (ft_strnequ(p->cache.str + i, old.str, len) && (done || p->g_flag))
		{
			done = FALSE;
			if (new.str)
				w_addstr(&p->tmp, new.str);
			i += len;
		}
		else
		{
			if (charcmp(p->cache.str, i, '&'))
			{
				if (new.str)
					w_addstr(&p->tmp, new.str);
			}
			else if (!charcmp(p->cache.str, i, '\\'))
				w_addchar(&p->tmp, p->cache.str[i]);
			++i;
		}
	}
	return (FALSE);
}

static int	apply_modifier(const char **source, struct s_parse_mod *p)
{
	int		done;

				char	delim;
				t_word	new;
				t_word	old;
				const char *s;

	ssize_t	h_i;
	ssize_t	h_end;

					ssize_t	t_i;

					ssize_t	r_i;
					ssize_t	r_end;

					ssize_t	e_i;

	done = TRUE;
	while (**source && done)
	{
		if (**source == 'q' || **source == 'x')
		{
			if (**source == 'q')
				p->quote_mode = 'q';
			else if (**source == 'x')
				p->quote_mode = 'x';
			++(*source);
		}
		else
		{
			if (**source == 'g' || **source == 's')
			{

				w_newword(&new);
				w_newword(&old);
				s = *source;
				if (**source == 'g')
				{
					p->g_flag = 1;
					++(*source);
					if (**source != 's')
						return (TRUE);
				}
				++(*source);
				delim = **source;
				if (!**source)
					return (TRUE);
				++(*source);
				while (**source && !charcmp(s, *source - s, delim))//charcmp
				{
					w_addchar(&old, **source);
					++(*source);
				}
				if (**source == delim)
					++(*source);
				while (**source && !charcmp(s, *source - s, delim) && **source != '\n')//charcmp
				{
					w_addchar(&new, **source);
					++(*source);
				}
				if (**source == delim)
					++(*source);
				if (perform_substitute(p, old, new))
					return (TRUE);
			}
			else
			{
				if (**source == 'h')
				{

					h_i = 0;
					h_end = ft_strrichr(p->cache.str, '/');
					while (p->cache.str[h_i] && h_i != h_end)
					{
						w_addchar(&p->tmp, p->cache.str[h_i]);
						++h_i;
					}
				}
				else if (**source == 't')
				{

					t_i = ft_strrichr(p->cache.str, '/');
					++t_i;
					while (p->cache.str[t_i])
					{
						w_addchar(&p->tmp, p->cache.str[t_i]);
						++t_i;
					}
				}
				else if (**source == 'r')
				{

					r_i = 0;
					r_end = ft_strrichr(p->cache.str, '.');
					while (p->cache.str[r_i] && r_i != r_end)
					{
						w_addchar(&p->tmp, p->cache.str[r_i]);
						++r_i;
					}
				}
				else if (**source == 'e')
				{

					e_i = ft_strrichr(p->cache.str, '.');
					++e_i;
					while (p->cache.str[e_i])
					{
						w_addchar(&p->tmp, p->cache.str[e_i]);
						++e_i;
					}
				}
				++(*source);
			}
			pop(&p->cache, &p->tmp);
		}
		if (valid_modifier(source, &done))
			return (TRUE);
	}
	return (FALSE);
}

static int apply_quotes(struct s_parse_mod *p)
{
	size_t	i;
	int		escape;

	i = 0;
	escape = FALSE;
	if (!p->cache.str)
		return (TRUE);
	w_addchar(&p->tmp, '\'');
	while (p->cache.str[i])
	{
		escape = FALSE;
		if (p->quote_mode == 'x' && ft_strchr("\t \n", p->cache.str[i]))
		{
			w_addchar(&p->tmp, '\'');
			escape = TRUE;
		}
		else if (p->cache.str[i] == '\'')
		{
			w_addchar(&p->tmp, '\'');
			w_addchar(&p->tmp, '\\');
			escape = TRUE;
		}
			w_addchar(&p->tmp, p->cache.str[i]);
		if (escape)
			w_addchar(&p->tmp, '\'');
		++i;
	}
	w_addchar(&p->tmp, '\'');
	pop(&p->cache, &p->tmp);
	return (FALSE);
}

int		modifier_expand(const char **source, t_word *ret, t_word word_designator, int *done)
{
	int		r;
	struct s_parse_mod p;

	*done = TRUE;
	r = valid_modifier(source, done);
	if (!*done)
		return (default_behavior(ret, word_designator));
	if (r)
		return (TRUE);
	w_newword(ret);
	init_p(&p, word_designator);
	if (apply_modifier(source, &p))
	{
		w_free(&p.cache);
		w_free(&p.tmp);
		return (TRUE);
	}
	if (p.quote_mode)
		apply_quotes(&p);
	if (p.cache.str)
		w_addstr(ret, p.cache.str);
	w_free(&p.cache);
	w_free(&p.tmp);
	return (FALSE);
}
