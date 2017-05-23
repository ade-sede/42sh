#include "libft.h"
#include "printf.h"

static short int		check_quotes_content(const char *str, const char *split_base, unsigned int *index)
{
	short int	in_quotes;
	short	int	word_in_quotes;
	unsigned int	i;

	word_in_quotes = false;
	in_quotes = true;
	i = *index;
	i++;
	while (str[i] && in_quotes)
	{
		if (charcmp(str, i, '"'))
			in_quotes = false;
		if (!ft_is_one_of(str[i], split_base) && !charcmp(str, i, '"'))
			word_in_quotes = true;
		i++;
	}
	*index = i;
	return (word_in_quotes);
}

static unsigned int	count_words(const char *str, const char *split_base)
{
	unsigned int	i;
	unsigned int	nb_words;
	short int		word_in_quotes;

	i = 0;
	nb_words = 0;
	word_in_quotes = false;
	while (str[i])
	{
		while (str[i] && ft_is_one_of(str[i], split_base) && !charcmp(str, i, '"'))
			i++;
		if (str[i] && charcmp(str, i, '"'))
			word_in_quotes = check_quotes_content(str, split_base, &i);
		if (str[i] && !(ft_is_one_of(str[i], split_base)) && !charcmp(str, i, '"'))
			nb_words++;
		while (str[i] && !(ft_is_one_of(str[i], split_base)) && !charcmp(str, i, '"'))
			i++;
		if (word_in_quotes)
			nb_words++;
		word_in_quotes = false;
	}
	return (nb_words);
}

static void	fill_word_tab(const char *str, const char *split_base, char **word_tab)
{
	unsigned int	i;
	short int		word_in_quotes;
	unsigned int	word_start;

	i = 0;
	word_in_quotes = false;
	while (str[i])
	{
		while (str[i] && ft_is_one_of(str[i], split_base) && !charcmp(str, i, '"'))
			i++;
		if (str[i] && charcmp(str, i, '"'))
		{
			word_start = i + 1;
			word_in_quotes = check_quotes_content(str, split_base, &i);
			if (word_in_quotes)
			{
				*word_tab = ft_strsub(str, word_start, (i - word_start) - 1);
				word_tab++;
			}
		}
		if (str[i] && !(ft_is_one_of(str[i], split_base)) && !charcmp(str, i, '"'))
		{
			word_start = i;
			while (str[i] && !(ft_is_one_of(str[i], split_base)) && !charcmp(str, i, '"'))
			{
				i++;
			}
			*word_tab = ft_strsub(str, word_start, (i - word_start));
			word_tab++;
		}
		word_in_quotes = false;
	}
}

char		**ft_strsplit_quotes(const char *str, const char *split_base)
{
	char			**word_tab;
	unsigned int	nb_words;

	word_tab = NULL;
	if (!str)
		return (NULL);
	nb_words = count_words(str, split_base);
	word_tab = palloc(sizeof(char*) * (nb_words + 1), __func__);
	word_tab[nb_words] = NULL;
	fill_word_tab(str, split_base, word_tab);
	return (word_tab);
}
