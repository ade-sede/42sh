#include "lexer.h"
#include "libft.h"




#include "color.h"
#include <stdio.h>

#ifdef LEXER_DEBUG
static struct s_debug_token_state g_debug_token_state[]=
{
	{DEFAULT,"DEFAULT"},
	{WORD,"WORD"},
	{WHITESPACE,"WHITESPACE"},
	{COMMENT,"COMMENT"},
	{OPERATOR,"OPERATOR"},
	{PARAM_EXP,"PARAM_EXP"},
	{CMD_SUBST,"CMD_SUBST"},
	{TILD_EXP,"TILD_EXP"}, {AR_EXP,"AR_EXP"},
	{DQUOTES,"DQUOTES"},
	{QUOTES,"QUOTES"},
	{BS,"BS"},
	{NEWLINE, "NEWLINE"},
	{-1, NULL}
};

static char	*get_state(int state)
{
	int	i = 0;

	while  (g_debug_token_state[i].state != state)
		++i;
	return (g_debug_token_state[i].name);
}
#endif

/*
**	List of utilities used for the lexer's stack discipline
*/

/*
**	Pushes a ssize_t* whose _T_STATE index is set to new_state.
**	_T_START set to lex->pos
**	_T_END set to -1 (undefined) **	_T_COUNT set to 0.  */ 

/* ssize_t	*create_state_info(void) */
/* { */
/* 	ssize_t	*info; */

/* 	info = palloc(sizeof(*info) * 5); */
/* 	ft_memset(info, 0, sizeof(*info) * 5); */
/* 	return (info); */
/* } */

void	free_info(void *ptr)
{
	struct s_info *info;

	info = ptr;
	if (info)
		free(info->value);
	free(info);
}

struct s_info	*create_state_info(void)
{
	struct s_info *info;

	info = palloc(sizeof(*info));
	ft_memset(info, 0, sizeof(*info));
	return (info);
}

/*
**	
*/

void	copy_state_info(struct s_info *old_info, struct s_info *new_info)
{
	ft_memcpy(new_info, old_info, sizeof(struct s_info));
}
/* void	copy_state_info(ssize_t *old_info, ssize_t *new_info) */
/* { */
/* 	new_info[_T_STATE] = old_info[_T_STATE]; */
/* 	new_info[_T_START] = old_info[_T_START]; */
/* 	new_info[_T_END] = old_info[_T_END]; */
/* 	new_info[_T_STATE] = old_info[_T_STATE]; */
/* 	new_info[_T_NEST] = old_info[_T_NEST]; */
/* } */

int		push_state(t_lexer *lex, int new_state)
{
	struct s_info *info;
	t_list *node;
#ifdef LEXER_DEBUG
	struct s_info	*old_state;

	if (lex->state)
	{
		old_state = lex->state->data;
		dprintf(2, GRN"Pushed "RESET"state %s when reading "MAG"#"CYN"%c"MAG"#"RESET" on index [%zu] in state %s\n", get_state(new_state), lex->line[lex->pos], lex->pos, get_state(old_state->state));
	}
#endif
	info = create_state_info();
	info->state = new_state;
	info->start = lex->pos;
	info->end = -1;
	info->nest = 0;
	node = ft_simple_lst_create(info);
	ft_simple_lst_pushback(&lex->state_list, node);
	lex->state = node;
	return (1);
}

/* int		push_state(t_lexer *lex, ssize_t new_state) */
/* { */
/* 	ssize_t	*info; */
/* 	t_list	*node; */

/* #ifdef LEXER_DEBUG */
/* 	ssize_t	*old_state; */

/* 	if (lex->state) */
/* 	{ */
/* 		old_state = lex->state->data; */
/* 		dprintf(2, GRN"Pushed "RESET"state %s when reading "MAG"#"CYN"%c"MAG"#"RESET" on index [%zu] in state %s\n", get_state(new_state), lex->line[lex->pos], lex->pos, get_state(old_state[_T_STATE])); */
/* 	} */
/* #endif */
/* 	info = create_state_info(); */
/* 	info[_T_STATE] = new_state; */
/* 	info[_T_START] = lex->pos; */
/* 	info[_T_END] = -1; */
/* 	info[_T_COUNT] = 0; */
/* 	info[_T_NEST] = 0; */
/* 	node = ft_simple_lst_create(info); */
/* 	ft_simple_lst_pushback(&lex->state_list, node); */
/* 	lex->state = node; */
/* 	return (1); */
/* } */

/* int		consume_input(t_lexer *lex) */
/* { */
/* 	ssize_t	*info; */

/* 	info = lex->state->data; */
/* #ifdef LEXER_DEBUG */
/* 		dprintf(2, YEL"Adding "MAG"#"CYN"%c"MAG"#"RESET" on index [%zu] to current state %s\n", lex->line[lex->pos], lex->pos, get_state(info[_T_STATE])); */
/* #endif */
/* 	lex->pos++; */
/* 	(info[_T_COUNT])++; */
/* 	return (1); */
/* } */

int		consume_input(t_lexer *lex)
{
	struct s_info	*info;
	info = lex->state->data;
#ifdef LEXER_DEBUG
		dprintf(2, YEL"Adding "MAG"#"CYN"%c"MAG"#"RESET" on index [%zu] to current state %s\n", lex->line[lex->pos], lex->pos, get_state(info->state));
#endif
	info->value = ft_realloc(info->count, info->value, info->count + 1);
	info->value[info->count] = lex->line[lex->pos];
	lex->pos++;
	info->count++;
	return (1);
}

/*
**	The cache info is freed and replaced by the one freshly
**	poped.
**	lex->pos - 1 is considered to be the end of the last token.
**	So closed token like quotes need to consume 1 more input before they
**	pop_state.
*/

int		pop_state(t_lexer *lex, struct s_info **info)
{
	struct s_info *old_info;
	struct s_info *new_info;
	
	free_info(*info);
	new_info = create_state_info();
	old_info = lex->state->data;
	old_info->end = lex->pos - 1;
	copy_state_info(old_info, new_info);
#ifdef LEXER_DEBUG
	dprintf(2, RED"Poped "RESET"state %s when reading "MAG"#"CYN"%c"MAG"#"RESET" on index [%zu]\n", get_state(old_info->state), lex->line[lex->pos], lex->pos);
#endif
	ft_simple_lst_del_one(&lex->state_list, lex->state, NULL);
	lex->state = ft_last_simple_lst(lex->state_list);
	*info = new_info;
	return (1);
}
/* int		pop_state(t_lexer *lex, ssize_t	**info) */
/* { */
/* 	ssize_t	*old_info; */
/* 	ssize_t	*new_info; */

/* 	free(*info); */
/* 	new_info = create_state_info(); */
/* 	old_info = lex->state->data; */
/* 	old_info[_T_END] = lex->pos - 1; */
/* 	copy_state_info(old_info, new_info); */
/* #ifdef LEXER_DEBUG */
/* 	dprintf(2, RED"Poped "RESET"state %s when reading "MAG"#"CYN"%c"MAG"#"RESET" on index [%zu]\n", get_state(old_info[_T_STATE]), lex->line[lex->pos], lex->pos); */
/* #endif */
/* 	ft_simple_lst_del_one(&lex->state_list, lex->state, NULL); */
/* 	lex->state = ft_last_simple_lst(lex->state_list); */
/* 	*info = new_info; */
/* 	return (1); */
/* } */

int			change_state(t_lexer *lex, int	new_state)
{
	
	((struct s_info*)lex->state->data)->state = new_state;
	return (1);
}

/* int		change_state(t_lexer *lex, ssize_t new_state) */
/* { */
/* 	((ssize_t*)lex->state->data)[_T_STATE] = new_state; */
/* 	return (0); */
/* } */
