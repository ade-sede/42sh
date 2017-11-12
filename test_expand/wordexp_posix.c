#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

char	**word_expansion (const char *words, int flag) // NO_GLOBING | NO_FIELD_SPLITTING
{
	size_t	offset;
	t_word	word;
	t_word	g_word;
	int error;
	char *ifs;
	t_expand exp;

	w_newword (&word);
	w_newword (&g_word);
	w_newexp (&exp);

//	ifs = env_getenv (singelton_env()->environ, "IFS", NULL);
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
			parse_dquote (&g_word, &word, words, &offset, &exp, ifs);
			if (!word.str && !words[1 + offset])
				w_addword (&exp, &g_word, &word);
		}
		else if (words[offset] == '\'')
		{
			++offset;
			parse_squote (&g_word, &word, words, &offset);
			if (!word.str && !words[1 + offset])
				w_addword (&exp, &g_word, &word);
		}
		/*
		   else if (words[offset] == '`')
		   {
		   ++offset;
		   parse_backtick (&word, &word_length, &max_length, words,
		   &offset, flags, pwordexp, ifs);
		   }
		   */
		   else if (words[offset] == '$')
			   parse_dollars (&g_word, &word, words, &offset, &exp, ifs, 0);
		   else if (words[offset] == '~')
			   parse_tilde (&g_word, &word, words, &offset);
		else
		{
//			printf("w: {%s}, gw: {%s}\nwsize: {%zu}, gwsize: {%zu}\n", word.str, g_word.str, word.actlen, g_word.actlen);
//			printf("wsize max: {%zu}, gwsize max: {%zu}\n", word.maxlen, g_word.maxlen);
			w_addchar (&word, words[offset]);
			w_addchar (&g_word, words[offset]);
		}
		offset++;
	}
	if (word.str != NULL)
		w_addword (&exp, &g_word, &word);
	int	i;
	for (i=0; i < exp.actlen; i++)
		printf("w: {%s}, gw: {%s}\n", exp.av_word[i], exp.av_gword[i]);
	getchar();
	return (exp.av_word);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("bad ac\n");
		return (1);
	}
	word_expansion(av[1], 0);
	return (0);
}
