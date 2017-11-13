#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

/*  after "$(" */

int		parse_comm (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted)
{
	int paren_depth = 1;
	int quoted = 0;
	t_word comm;

	w_newword (&comm);
	while (words[*offset])
	{
		if (words[*offset] == '\'')
		{
			if (quoted == 0)
				quoted = 1;
			else if (quoted == 1)
				quoted = 0;
		}
		if (words[*offset] == '"')
		{
			if (quoted == 0)
				quoted = 2;
			else if (quoted == 2)
				quoted = 0;
		}
		if (words[*offset] == ')')
		{
			if (!quoted && --paren_depth == 0)
			{
				if (comm.str)
				{
					error = exec_comm (comm, flags, pwordexp, ifs);
					free (comm);
					return error;
				}
			}
			if (words[*offset] == '(' && !quoted)
				++paren_depth;
			w_addchar (comm, words[*offset]);
			++(*offset);
		}
		free (comm);

		return WRDE_SYNTAX;
	}


