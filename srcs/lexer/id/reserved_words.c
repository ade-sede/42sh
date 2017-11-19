#include "lexer.h"
#include "libft.h"

char	*g_reserved_word_list[] =
{
	"if",
	"then",
	"else",
	"elif",
	"fi",
	"do",
	"done",
	"case",
	"esac",
	"while",
	"until",
	"for",
	"{",
	"}",
	"!",
	"(",
	")",
	"in",
	NULL
};

int		id_reserved_words(const char *value)
{
	int		id;
	size_t	i;

	i = 0;
	id = -1;
	while (g_reserved_word_list[i] && !ft_strequ(g_reserved_word_list[i], value))
		++i;
	if (g_reserved_word_list[i])
		id = i + RESERVED_WORDS_OFFSET;
	else
		id = 0;
	return (id);
}
