#include "expand.h"
#include "libft.h"

int		handle_fieldsplitting (char *value, t_expand *exp)
{
	if (!value)
		return (0);
	if (exp->quoted || !exp)
	{
		/* no field-split */
		size_t		i = 0;
		while (value[i])
		{
			if (value[i] == '\\')
				parse_qtd_backslash (&exp->g_word, &exp->word, value, &i); //TODO: effet de bord
			else if (ft_strchr("*[?", value[i]))
			{
				w_addchar (&exp->g_word, '\\');
				w_addchar (&exp->g_word, value[i]); 
				w_addchar (&exp->word, value[i]);
			}
			else
			{
				w_addchar (&exp->g_word, value[i]);
				w_addchar (&exp->word, value[i]);
			}
			i++;
		}
		return 0;
	}
	else
	{
		/* Need to field-split */
		char	**split = ft_strsplit(value, exp->ifs);
		size_t		i;
		w_addstr (&exp->word, split[0]);
		w_addstr (&exp->g_word, split[0]);
		i = 1;
		while (split[i])
		{
			w_addword (exp, &exp->g_word, &exp->word);
//			fprint(stderr,"split[i]: %s\n", split[i]);
			w_addstr (&exp->word, split[i]);
			w_addstr (&exp->g_word, split[i]);
			i++;
		}
		ft_arraydel(&split);
	}
	return (0);
}
