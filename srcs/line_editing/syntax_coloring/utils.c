#include "syntax_coloring.h"
#include "libft.h"
#include "color.h"

/*
**	ATM colors are hard-coded, but they should be retrieved from local variables in the future.
*/

static struct
{
	ssize_t		state;
	char		*color;
} g_color_struct[] =
{
	{DEFAULT, RESET},
	{DQUOTES, YEL},
	{PARAM_EXP, YEL},
	{WHITESPACE, RESET},
	{-1, NULL},
};

char	*get_color(ssize_t *state, int cmd_name)
{
	size_t	i;

	i = 0;
	while (g_color_struct[i].state != -1 && g_color_struct[i].state != state[_T_STATE])
		++i;
	if (g_color_struct[i].color == NULL)
		return ("");
	return (g_color_struct[i].color);
	(void)cmd_name;
}

ssize_t	*create_state_info_le(void)
{
	ssize_t	*info;

	info = palloc(sizeof(*info) * 5);
	ft_memset(info, 0, sizeof(*info) * 5);
	return (info);
}

void	copy_state_info_le(ssize_t *old_info, ssize_t *new_info)
{
	new_info[_T_STATE] = old_info[_T_STATE];
	new_info[_T_START] = old_info[_T_START];
	new_info[_T_END] = old_info[_T_END];
	new_info[_T_STATE] = old_info[_T_STATE];
	new_info[_T_NEST] = old_info[_T_NEST];
}

int		push_state_le(t_lexer *lex, ssize_t new_state)
{
	ssize_t	*info;
	t_list	*node;

	info = create_state_info_le();
	info[_T_STATE] = new_state;
	info[_T_START] = lex->pos;
	info[_T_END] = -1;
	info[_T_COUNT] = 0;
	info[_T_NEST] = 0;
	node = ft_simple_lst_create(info);
	ft_simple_lst_pushback(&lex->state_list, node);
	lex->state = node;
	/* Enter new color */
	ft_putstr_fd(get_color(info, lex->cmd_name_open), 2);
	return (1);
}

int		consume_input_le(t_lexer *lex, t_line *line)
{
	ssize_t	*info;

	write_term(line, lex->pos);

	info = lex->state->data;
	lex->pos++;
	(info[_T_COUNT])++;
	return (1);
}

int		pop_state_le(t_lexer *lex, ssize_t	**info)
{
	ssize_t	*old_info;
	ssize_t	*new_info;
	ssize_t	*color_info;

	/*
	**	Close color and enter color of the state we come back to.
	*/
	free(*info);
	new_info = create_state_info_le();
	old_info = lex->state->data;
	old_info[_T_END] = lex->pos - 1;
	copy_state_info_le(old_info, new_info);
	ft_simple_lst_del_one(&lex->state_list, lex->state, NULL);
	lex->state = ft_last_simple_lst(lex->state_list);
	*info = new_info;
	color_info = lex->state->data;
	ft_putstr_fd(get_color(color_info, lex->cmd_name_open), 2);
	return (1);
}

int		change_state_le(t_lexer *lex, ssize_t new_state)
{
	((ssize_t*)lex->state->data)[_T_STATE] = new_state;
	return (0);
}
