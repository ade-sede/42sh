#include "libft.h"
#include "pipe.h"
#include "t_token.h"
#include "failure.h"

/*
**	Those functions are called by the parser in file parser.c to edit the list
**	of pipes.
*/

/*
**	add_last_pipe adds an empty node at the end of the list of pipes and
**	creates the list if needed. Is called only once, when the parsing is over.
*/

void	add_last_pipe(t_lst_head **head)
{
	if (*head == NULL)
		*head = ft_create_head(ft_double_lst_create(NULL));
	else
	{
		ft_double_lst_pushback(head, ft_double_lst_create(NULL));
		(*head)->middle = (*head)->first;
	}
}

/*
**		add_pipe creates a full node and adds it to the list of pipes and
**		creates the list if needed.
*/

int		add_pipe(t_token *token, t_lst_head **head)
{
	t_pipe	*spipe;
	int		*p;

	spipe = NULL;
	p = NULL;
	if (ft_strequ(token->value, "|"))
	{
		p = palloc(sizeof(*p) * 2);
		if (pipe(p) != 0)
			return (investigate_error(1, "pipe", NULL, 0));
	}
	spipe = create_pipe(p);
	if (*head == NULL)
		*head = ft_create_head(ft_double_lst_create(spipe));
	else
		ft_double_lst_pushback(head, ft_double_lst_create(spipe));
	return (1);
}
