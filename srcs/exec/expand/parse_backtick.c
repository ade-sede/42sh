#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

/*  after "`" */
int		parse_backtick (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted)
{
	t_word comm;
	w_newword (&comm);

	while (words[*offset])
	{
		if (words[*offset] == '`')
		{
			exec_comm (comm, word, word_length, max_length, flags,
					pwordexp, ifs, ifs_white);
			return 0;
		}
		else
			w_addchar (comm, words[*offset]);
		++(*offset);
	}
	free (comm);
	return WRDE_SYNTAX;
}

