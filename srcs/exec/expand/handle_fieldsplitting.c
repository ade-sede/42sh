#include "expand.h"
#include "libft.h"

int		handle_fieldsplitting (char *value, t_word *g_word, t_word *word,	
		t_expand *exp, const char *ifs, int quoted)
{
	if (!value)
		return (0);
	if (quoted || !exp)
	{
		/* no field-split */
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
			i++;
		}
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
//			fprint(stderr,"split[i]: %s\n", split[i]);
			w_addstr (word, split[i]);
			w_addstr (g_word, split[i]);
			i++;
		}
		ft_arraydel(&split);
	}
	return (0);
}
