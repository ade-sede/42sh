#include "t_lexer.h"
#include "t_token.h"
#include "libft.h"

/*
**	List of utilities used for the lexer's stack discipline
*/

/*
**	Pushes a ssize_t* whose _T_STATE index is set to new_state.
**	_T_START set to lex->pos
**	_T_END set to -1 (undefined)
**	_T_COUNT set to 0.
*/

ssize_t	*create_state_info(void)
{
	ssize_t	*info;

	info = palloc(sizeof(*info) * 4);
	ft_memset(info, 0, sizeof(*info) * 4);
	return (info);
}

int		push_state(t_lexer *lex, ssize_t new_state)
{
	ssize_t	*info;
	t_list	*node;

	info = create_state_info();
	info[_T_STATE] = new_state;
	info[_T_START] = lex->pos;
	info[_T_END] = -1;
	info[_T_COUNT] = 0;
	node = ft_simple_lst_create(info);
	ft_simple_lst_pushback(&lex->state_list, node);
	lex->state = node;
	return (1);
}

int		pop_state(t_lexer *lex, ssize_t	**new_info)
{
	ssize_t	*old_info;
	ssize_t	*state_info;

	free(*new_info);
	state_info = create_state_info();
	old_info = lex->state->data;
	state_info[_T_STATE] = old_info[_T_STATE];
	state_info[_T_START] = old_info[_T_START];
	state_info[_T_END] = old_info[_T_END];
	state_info[_T_STATE] = old_info[_T_STATE];
	ft_simple_lst_del_one(&lex->state_list, lex->state);
	lex->state = ft_last_simple_lst(lex->state_list);
	*new_info = state_info;
	return (1);
}

int		change_state(t_lexer *lex, ssize_t new_state)
{
	lex->state->data[_T_STATE] = new_state;
}
